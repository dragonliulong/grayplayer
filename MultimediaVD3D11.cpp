#include "MultimediaDecodeSetting.h"
#include "MultimediaVD3D11.h"
#include "MultimediaResource.h"
#include "MultimediaFilter.h"
#include <QDebug>

VideoD3D11::VideoD3D11(QWidget* parent) : QWidget(parent)
{
    d3d11Device=NULL;
    d3d11DeviceContext=NULL;
    d3d11VideoDevice=NULL;
    d3d11VideoContext=NULL;
    d3d11VideoProcessorEnumerator=NULL;
    d3d11VideoProcessor=NULL;
    videoW=0;
    videoH=0;
    areaW=0;
    areaH=0;
    cur_swap_chain_id=0;

    connect(this,&VideoD3D11::showInUiNow,this,&VideoD3D11::show);
    connect(this,&VideoD3D11::hideInUiNow,this,&VideoD3D11::hide);

    setMouseTracking(true);  //设置鼠标监控
    setUpdatesEnabled(false); //关闭update
    hide(); //隐藏
}

void VideoD3D11::showInUi()
{
    emit showInUiNow();
}

int VideoD3D11::enumAdapters()
{
    IDXGIFactory* factory = NULL;
    CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
    IDXGIAdapter* adapter = NULL;

    //默认适配器
    adapters.push_back(NULL);

    for( UINT i = 0; factory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND; i++)
        adapters.push_back(adapter);

    factory->Release();
    return adapters.size();
}

void VideoD3D11::initD3D11(int w, int h)
{
    areaW=0;
    areaH=0;
    videoW = w;
    videoH = h;

    //--------------------------d3d11交换链参数-----------------------------

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

    swapChainDesc.Windowed = TRUE;
    swapChainDesc.OutputWindow = (HWND)winId();
    swapChainDesc.BufferDesc.Format = dxgi_format;    //交换链buffer格式
    swapChainDesc.SwapEffect = dxgi_swap_effect;      //交换效果

    //交换链buffer数 (根据交换效果设置)
    swapChainDesc.BufferCount =
            (dxgi_swap_effect == DXGI_SWAP_EFFECT_DISCARD || dxgi_swap_effect == DXGI_SWAP_EFFECT_SEQUENTIAL) ? 1 : 2;

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferDesc.Width = videoW;
    swapChainDesc.BufferDesc.Height = videoH;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    //-----------------------------d3d硬件支持级别------------------------------------

    D3D_FEATURE_LEVEL levels[6]=
    {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    UINT level_count = 6;

    //--------------------------根据选择的适配器创建d3d11设备----------------------------

    IDXGIAdapter* adapter = adapters[adapter_choice];
    D3D_DRIVER_TYPE d3d_drive_type = adapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE;

    D3D11CreateDevice( adapter, d3d_drive_type,
                       NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                       levels, level_count,
                       D3D11_SDK_VERSION, &d3d11Device,
                       NULL, &d3d11DeviceContext );

    //--------------------------创建交换链----------------------------

    IDXGIFactory* factory = NULL;
    CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);

    for(int i = 0; i < swap_chain_count; i++)
    {
        IDXGISwapChain* swapChain = NULL;
        factory->CreateSwapChain(d3d11Device, &swapChainDesc, &swapChain);
        swapChains.push_back(swapChain);
    }

    factory->Release();

    //-------------------------------------------------------------

    //交换链是否存在数据和当前交换链
    existData.assign(swap_chain_count, 0);
    cur_swap_chain_id = 0;
}

void VideoD3D11::turnToNextSwapChain()
{
    cur_swap_chain_id = (cur_swap_chain_id + 1) % swap_chain_count;
}

void VideoD3D11::prepare(AVFrame* frame)
{
    //创建intputView
    ID3D11VideoProcessorInputView* inputView = NULL;
    D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC inputViewDesc;
    ZeroMemory(&inputViewDesc, sizeof(inputViewDesc));
    inputViewDesc.ViewDimension = D3D11_VPIV_DIMENSION_TEXTURE2D;
    inputViewDesc.Texture2D.ArraySlice = (intptr_t)frame->data[1];  //重要参数，指定纹理索引
    d3d11VideoDevice->CreateVideoProcessorInputView((ID3D11Texture2D*)frame->data[0], d3d11VideoProcessorEnumerator, &inputViewDesc, &inputView);

    //创建outputView
    ID3D11VideoProcessorOutputView* outputView = NULL;
    D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC outputViewDesc;
    ZeroMemory(&outputViewDesc, sizeof(outputViewDesc));
    outputViewDesc.ViewDimension = D3D11_VPOV_DIMENSION_TEXTURE2D;

    ID3D11Texture2D* buffer = NULL;
    swapChains[cur_swap_chain_id]->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer); //获取当前交换链buffer

    d3d11VideoDevice->CreateVideoProcessorOutputView(buffer, d3d11VideoProcessorEnumerator, &outputViewDesc, &outputView);

    //流
    D3D11_VIDEO_PROCESSOR_STREAM stream;
    ZeroMemory(&stream, sizeof(stream));
    stream.Enable = TRUE;
    stream.pInputSurface = inputView;

    RECT rect=
    {
        .left = 0,
        .top = 0,
        .right = videoW,
        .bottom = videoH
    };

    d3d11VideoContext->VideoProcessorSetStreamSourceRect(d3d11VideoProcessor, 0, TRUE, &rect);

    //滤镜
    D3D11VAFilter filter = getD3D11VAFilter();
    d3d11VideoContext->VideoProcessorSetStreamFilter(d3d11VideoProcessor, 0, D3D11_VIDEO_PROCESSOR_FILTER_BRIGHTNESS, TRUE, filter.brightness);
    d3d11VideoContext->VideoProcessorSetStreamFilter(d3d11VideoProcessor, 0, D3D11_VIDEO_PROCESSOR_FILTER_CONTRAST, TRUE, filter.contrast);
    d3d11VideoContext->VideoProcessorSetStreamFilter(d3d11VideoProcessor, 0, D3D11_VIDEO_PROCESSOR_FILTER_HUE, TRUE, filter.hue);
    d3d11VideoContext->VideoProcessorSetStreamFilter(d3d11VideoProcessor, 0, D3D11_VIDEO_PROCESSOR_FILTER_SATURATION, TRUE, filter.saturation);
    d3d11VideoContext->VideoProcessorSetStreamFilter(d3d11VideoProcessor, 0, D3D11_VIDEO_PROCESSOR_FILTER_EDGE_ENHANCEMENT, TRUE, filter.edge_enhancement);

    //处理
    d3d11VideoContext->VideoProcessorBlt(d3d11VideoProcessor, outputView, 0, 1, &stream);

    //释放资源
    inputView->Release();
    outputView->Release();
    buffer->Release();

    //准备完成, 当前交换链存在数据
    existData[cur_swap_chain_id] = 1;
}

void VideoD3D11::present()
{
    swapChains[cur_swap_chain_id]->Present(1, 0);  //一个垂直同步
}

bool VideoD3D11::existDataInCurSwapChain()
{
    return existData[cur_swap_chain_id];
}

void VideoD3D11::createVideoProcessor()
{
    D3D11_VIDEO_PROCESSOR_CONTENT_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.InputFrameFormat = D3D11_VIDEO_FRAME_FORMAT_PROGRESSIVE;
    desc.InputWidth = videoW;
    desc.InputHeight = videoH;
    desc.OutputWidth = videoW;
    desc.OutputHeight = videoH;
    desc.Usage = D3D11_VIDEO_USAGE_PLAYBACK_NORMAL;
    d3d11VideoDevice->CreateVideoProcessorEnumerator(&desc, &d3d11VideoProcessorEnumerator);

    D3D11_VIDEO_PROCESSOR_CAPS caps;
    d3d11VideoProcessorEnumerator->GetVideoProcessorCaps(&caps);

    for(UINT index = 0; index < caps.RateConversionCapsCount; index++)
    {
        HRESULT hr = d3d11VideoDevice->CreateVideoProcessor(d3d11VideoProcessorEnumerator, index, &d3d11VideoProcessor);
        if(hr == S_OK) break;
    }

    //------------------------设置滤镜值范围---------------------------

    D3D11_VIDEO_PROCESSOR_FILTER_RANGE range;
    D3D11VAFilterRange d3d11vaFilterRange;

    d3d11VideoProcessorEnumerator->GetVideoProcessorFilterRange(D3D11_VIDEO_PROCESSOR_FILTER_BRIGHTNESS, &range);
    d3d11vaFilterRange.brightness_range = range;

    d3d11VideoProcessorEnumerator->GetVideoProcessorFilterRange(D3D11_VIDEO_PROCESSOR_FILTER_CONTRAST, &range);
    d3d11vaFilterRange.contrast_range = range;

    d3d11VideoProcessorEnumerator->GetVideoProcessorFilterRange(D3D11_VIDEO_PROCESSOR_FILTER_HUE, &range);
    d3d11vaFilterRange.hue_range = range;

    d3d11VideoProcessorEnumerator->GetVideoProcessorFilterRange(D3D11_VIDEO_PROCESSOR_FILTER_SATURATION, &range);
    d3d11vaFilterRange.saturation_range = range;

    d3d11VideoProcessorEnumerator->GetVideoProcessorFilterRange(D3D11_VIDEO_PROCESSOR_FILTER_EDGE_ENHANCEMENT, &range);
    d3d11vaFilterRange.edge_enhancement_range = range;

    setD3D11VAFilterRange(&d3d11vaFilterRange);
    emit showFilterNow();

    //----------------------------------------------------------------
}

void VideoD3D11::d3d11va_device_create(AVCodecContext* codecCtx)
{
    AVBufferRef* deviceRef = av_hwdevice_ctx_alloc(HW_D3D11VA);

    //---------------------------------------------------------------------------

    AVHWDeviceContext* deviceCtx = (AVHWDeviceContext*)deviceRef->data;
    AVD3D11VADeviceContext* hwctx = (AVD3D11VADeviceContext*)deviceCtx->hwctx;

    hwctx->device = d3d11Device;
    hwctx->device_context = d3d11DeviceContext;

    av_hwdevice_ctx_init(deviceRef);

    d3d11VideoDevice = hwctx->video_device;
    d3d11VideoContext = hwctx->video_context;

    createVideoProcessor();

    //---------------------------------------------------------------------------

    codecCtx->hw_device_ctx = av_buffer_ref(deviceRef);
}

void VideoD3D11::resizeD3D11()
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

void VideoD3D11::freeResourceAndHide()
{
    for(int i=0; i<(int)swapChains.size(); i++)
        swapChains[i]->Release();

    while(!swapChains.empty())
        swapChains.pop_back();

    d3d11Device->Release();
    d3d11DeviceContext->Release();
    d3d11VideoDevice->Release();
    d3d11VideoContext->Release();
    d3d11VideoProcessorEnumerator->Release();
    d3d11VideoProcessor->Release();

    d3d11Device=NULL;
    d3d11DeviceContext=NULL;
    d3d11VideoDevice=NULL;
    d3d11VideoContext=NULL;
    d3d11VideoProcessorEnumerator=NULL;
    d3d11VideoProcessor=NULL;

    videoW=0;
    videoH=0;
    areaW=0;
    areaH=0;
    cur_swap_chain_id = 0;
    existData.clear();

    emit hideInUiNow();
    emit hideFilterNow();
}

//videoD3D11
VideoD3D11* videoD3D11=NULL;
