#include "MultimediaVD3D9.h"
#include "MultimediaResource.h"
#include "MultimediaDecodeSetting.h"
#include <QDebug>

VideoD3D9::VideoD3D9(QWidget* parent) : QWidget(parent)
{
    //创建d3d9和设备管理器, 将一直存在, 直到程序退出
    Direct3DCreate9Ex(D3D_SDK_VERSION, &d3d9Ex);
    DXVA2CreateDirect3DDeviceManager9(&resetToken, &d3d9DeviceManager);

    d3d9DeviceEx=NULL;
    videoW=0;
    videoH=0;
    areaW=0;
    areaH=0;

    hd_device=NULL;
    hd_processor=NULL;

    //获取DXVAHD接口
    getDXVAHDFunctions();

    connect(this,&VideoD3D9::showInUiNow,this,&VideoD3D9::show);
    connect(this,&VideoD3D9::hideInUiNow,this,&VideoD3D9::hide);

    setMouseTracking(true);  //设置鼠标监控
    setUpdatesEnabled(false); //关闭update
    hide(); //隐藏
}

void VideoD3D9::showInUi()
{
    emit showInUiNow();
}

void VideoD3D9::getDXVAHDFunctions()
{
    QLibrary dll("DXVA2_DLL.dll");

    DXVAHD_CreateDevice = (DXVAHD_CreateDevice_FUN)dll.resolve("DXVAHD_CreateDevice_FUN");
    HD_GetVideoProcessorDeviceCaps = (HD_GetVideoProcessorDeviceCaps_FUN)dll.resolve("HD_GetVideoProcessorDeviceCaps_FUN");
    HD_GetVideoProcessorCaps = (HD_GetVideoProcessorCaps_FUN)dll.resolve("HD_GetVideoProcessorCaps_FUN");
    HD_GetVideoProcessorFilterRange = (HD_GetVideoProcessorFilterRange_FUN)dll.resolve("HD_GetVideoProcessorFilterRange_FUN");
    HD_CreateVideoProcessor = (HD_CreateVideoProcessor_FUN)dll.resolve("HD_CreateVideoProcessor_FUN");
    HD_GetVideoProcessStreamState = (HD_GetVideoProcessStreamState_FUN)dll.resolve("HD_GetVideoProcessStreamState_FUN");
    HD_SetVideoProcessStreamState = (HD_SetVideoProcessStreamState_FUN)dll.resolve("HD_SetVideoProcessStreamState_FUN");
    HD_SetVideoProcessBltState = (HD_SetVideoProcessBltState_FUN)dll.resolve("HD_SetVideoProcessBltState_FUN");
    HD_VideoProcessBltHD = (HD_VideoProcessBltHD_FUN)dll.resolve("HD_VideoProcessBltHD_FUN");
    HD_DeviceRelease = (HD_DeviceRelease_FUN)dll.resolve("HD_DeviceRelease_FUN");
    HD_ProcessorRelease = (HD_ProcessorRelease_FUN)dll.resolve("HD_ProcessorRelease_FUN");
}

void VideoD3D9::filterSrcToDst(IDirect3DSurface9* src, IDirect3DSurface9* dst)
{
    D3DSURFACE_DESC src_desc;
    src->GetDesc(&src_desc);

    DXVAHD_STREAM_STATE_D3DFORMAT_DATA src_format = { src_desc.Format };
    HD_SetVideoProcessStreamState(hd_processor, 0,  DXVAHD_STREAM_STATE_D3DFORMAT, sizeof(src_format), &src_format);

    DXVAHD_STREAM_STATE_SOURCE_RECT_DATA src_rect = { TRUE, RECT{ 0, 0, videoW, videoH } };
    HD_SetVideoProcessStreamState(hd_processor, 0,  DXVAHD_STREAM_STATE_SOURCE_RECT, sizeof(src_rect), &src_rect);

    DXVAHD_STREAM_STATE_DESTINATION_RECT_DATA dst_rect = { TRUE, RECT{ 0, 0, videoW, videoH } };
    HD_SetVideoProcessStreamState(hd_processor, 0,  DXVAHD_STREAM_STATE_DESTINATION_RECT, sizeof(dst_rect), &dst_rect);

    //---------------------------------------滤镜----------------------------------------------

    DXVAHDFilter filter = getDXVAHDFilter();
    DXVAHD_STREAM_STATE_FILTER_DATA stream_filter;

    stream_filter = { TRUE, filter.brightness };
    HD_SetVideoProcessStreamState(hd_processor, 0, DXVAHD_STREAM_STATE_FILTER_BRIGHTNESS, sizeof(stream_filter), &stream_filter);

    stream_filter = { TRUE, filter.contrast };
    HD_SetVideoProcessStreamState(hd_processor, 0, DXVAHD_STREAM_STATE_FILTER_CONTRAST, sizeof(stream_filter), &stream_filter);

    stream_filter = { TRUE, filter.hue };
    HD_SetVideoProcessStreamState(hd_processor, 0, DXVAHD_STREAM_STATE_FILTER_HUE, sizeof(stream_filter), &stream_filter);

    stream_filter = { TRUE, filter.saturation };
    HD_SetVideoProcessStreamState(hd_processor, 0, DXVAHD_STREAM_STATE_FILTER_SATURATION, sizeof(stream_filter), &stream_filter);

    stream_filter = { TRUE, filter.edge_enhancement };
    HD_SetVideoProcessStreamState(hd_processor, 0, DXVAHD_STREAM_STATE_FILTER_EDGE_ENHANCEMENT, sizeof(stream_filter), &stream_filter);

    //-----------------------------------------------------------------------------------------

    DXVAHD_STREAM_DATA stream;
    ZeroMemory(&stream, sizeof(stream));
    stream.Enable = TRUE;
    stream.pInputSurface = src;

    HD_VideoProcessBltHD(hd_processor, dst, 0, 1, &stream);
}

void VideoD3D9::createVideoProcessor()
{
    DXVAHD_CONTENT_DESC hd_desc;
    hd_desc.InputFrameFormat = DXVAHD_FRAME_FORMAT_PROGRESSIVE;
    hd_desc.InputWidth = videoW;
    hd_desc.InputHeight = videoH;
    hd_desc.OutputWidth = videoW;
    hd_desc.OutputHeight = videoH;

    DXVAHD_CreateDevice(d3d9DeviceEx, &hd_desc, DXVAHD_DEVICE_USAGE_PLAYBACK_NORMAL, NULL, &hd_device);

    DXVAHD_VPDEVCAPS device_caps;
    HD_GetVideoProcessorDeviceCaps(hd_device, &device_caps);

    const int count = device_caps.VideoProcessorCount;
    DXVAHD_VPCAPS caps[count];
    HD_GetVideoProcessorCaps(hd_device, count, caps);

    for(UINT i=0; i < device_caps.VideoProcessorCount; i++)
    {
        HRESULT hr = HD_CreateVideoProcessor(hd_device, &caps[i].VPGuid, &hd_processor);
        if(hr == S_OK) break;
    }

    //------------------------设置滤镜值范围---------------------------

    DXVAHD_FILTER_RANGE_DATA range;
    DXVAHDFilterRange dxvahdFilterRange;

    HD_GetVideoProcessorFilterRange(hd_device, DXVAHD_FILTER_BRIGHTNESS, &range);
    dxvahdFilterRange.brightness_range = range;

    HD_GetVideoProcessorFilterRange(hd_device, DXVAHD_FILTER_CONTRAST, &range);
    dxvahdFilterRange.contrast_range = range;

    HD_GetVideoProcessorFilterRange(hd_device, DXVAHD_FILTER_HUE, &range);
    dxvahdFilterRange.hue_range = range;

    HD_GetVideoProcessorFilterRange(hd_device, DXVAHD_FILTER_SATURATION, &range);
    dxvahdFilterRange.saturation_range = range;

    HD_GetVideoProcessorFilterRange(hd_device, DXVAHD_FILTER_EDGE_ENHANCEMENT, &range);
    dxvahdFilterRange.edge_enhancement_range = range;

    setDXVAHDFilterRange(&dxvahdFilterRange);
    emit showFilterNow();
}

void VideoD3D9::initD3D9(int w, int h)
{
    areaW=0;
    areaH=0;
    videoW=w;
    videoH=h;

    //--------------------------d3d9展示参数-----------------------------

    D3DPRESENT_PARAMETERS d3dpar;
    ZeroMemory(&d3dpar, sizeof(d3dpar));

    d3dpar.Windowed = TRUE;
    d3dpar.hDeviceWindow = (HWND)winId();
    d3dpar.SwapEffect = flipex_mode ? D3DSWAPEFFECT_FLIPEX : D3DSWAPEFFECT_DISCARD;  //交换效果
    d3dpar.PresentationInterval = D3DPRESENT_INTERVAL_ONE;  //一个垂直同步
    d3dpar.BackBufferFormat = D3DFMT_UNKNOWN;  //自动设置format
    d3dpar.BackBufferCount = 1;
    d3dpar.BackBufferWidth = videoW;
    d3dpar.BackBufferHeight = videoH;

    //---------------------------创建d3d9设备---------------------------

    d3d9Ex->CreateDeviceEx( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, (HWND)winId(),
                            D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                            &d3dpar, NULL, &d3d9DeviceEx );

    //-----------------------------------------------------------------

    //为设备管理器重置设备
    d3d9DeviceManager->ResetDevice(d3d9DeviceEx, resetToken);
}

void VideoD3D9::dxva2_device_create(AVCodecContext* codecCtx)
{
    AVBufferRef* deviceRef = av_hwdevice_ctx_alloc(HW_DXVA2);

    //-----------------------------------------------------------------------------------

    AVHWDeviceContext* deviceCtx = (AVHWDeviceContext*)deviceRef->data;
    AVDXVA2DeviceContext* hwctx = (AVDXVA2DeviceContext*)deviceCtx->hwctx;
    hwctx->devmgr = d3d9DeviceManager;
    av_hwdevice_ctx_init(deviceRef);

    //解码方式为DXVA2则创建视频处理器
    if(decodeMode == DXVA2)
        createVideoProcessor();

    //-------------------------------------------------------------------------------------

    codecCtx->hw_device_ctx = av_buffer_ref(deviceRef);
}

void VideoD3D9::prepare(AVFrame* frame)
{
    if(decodeMode == DXVA2) prepareSurface(frame);
    else prepareYUV(frame);
}

void VideoD3D9::prepareSurface(AVFrame* frame)
{
    IDirect3DSurface9* backBuffer = NULL;

    //获取交换链buffer
    d3d9DeviceEx->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

    //转换
    filterSrcToDst((IDirect3DSurface9*)frame->data[3], backBuffer);

    backBuffer->Release();
}

void VideoD3D9::prepareYUV(AVFrame* frame)
{
    IDirect3DSurface9* backBuffer = NULL;
    IDirect3DSurface9* offsurface = NULL;

    //获取交换链buffer
    d3d9DeviceEx->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

    //创建YUV420离屏表面
    d3d9DeviceEx->CreateOffscreenPlainSurface( videoW, videoH,
                                               (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'), D3DPOOL_DEFAULT,
                                               &offsurface, NULL);

    //----------------------------------------上传数据---------------------------------------------

    D3DLOCKED_RECT locked_rect;
    offsurface->LockRect(&locked_rect, NULL, D3DLOCK_DONOTWAIT);

    SwsContext* swsCtx = sws_getContext(videoW, videoH, (AVPixelFormat)frame->format,
                                        videoW, videoH, AV_PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);

    uint8_t* dst[] =
    {
        (uint8_t*)locked_rect.pBits,
        (uint8_t*)locked_rect.pBits + locked_rect.Pitch * videoH * 5/4,
        (uint8_t*)locked_rect.pBits + locked_rect.Pitch * videoH
    };

    int pitchs[] =
    {
        locked_rect.Pitch,
        locked_rect.Pitch/2,
        locked_rect.Pitch/2
    };

    sws_scale(swsCtx, frame->data, frame->linesize, 0, videoH, dst, pitchs);

    offsurface->UnlockRect();

    //----------------------------------------------------------------------------------------

    RECT rect=
    {
        .left = 0,
        .top = 0,
        .right = videoW,
        .bottom = videoH
    };

    d3d9DeviceEx->StretchRect(offsurface, &rect, backBuffer, &rect, D3DTEXF_LINEAR);

    //释放
    backBuffer->Release();
    offsurface->Release();
    sws_freeContext(swsCtx);
}

void VideoD3D9::present()
{
    d3d9DeviceEx->Present(NULL, NULL, NULL, NULL);
}

void VideoD3D9::resizeD3D9()
{
    if(!parentWidget()) return;
    if(parentWidget()->width() == areaW && parentWidget()->height() == areaH) return;

    areaW = parentWidget()->width();
    areaH = parentWidget()->height();

    double p1 = (double)videoW/(double)videoH;
    double p2 = (double)areaW/(double)areaH;

    int targetW, targetH;

    if(p1 < p2)
    {
        targetW = p1 * areaH;
        targetH = areaH;
    }
    else
    {
        targetH = areaW / p1;
        targetW = areaW;
    }

    int targetX = (areaW - targetW) / 2;
    int targetY = (areaH - targetH) / 2;

    setGeometry(targetX, targetY, targetW, targetH);
}

void VideoD3D9::freeResourceAndHide()
{
    d3d9DeviceEx->Release();
    d3d9DeviceEx=NULL;

    if(hd_device)
    {
        HD_DeviceRelease(hd_device);
        hd_device=NULL;
    }

    if(hd_processor)
    {
        HD_ProcessorRelease(hd_processor);
        hd_processor=NULL;
    }

    videoW=0;
    videoH=0;
    areaW=0;
    areaH=0;

    emit hideInUiNow();
    emit hideFilterNow();
}

//videoD3D9
VideoD3D9* videoD3D9=NULL;
