#include "MultimediaVD3D9.h"
#include "MultimediaDecodeSetting.h"
#include "MultimediaMain.h"

void VideoD3D9::setFullScreenFlag(bool f)
{
    mut.lock();
    fullScreenFlag = f;
    mut.unlock();
}

bool VideoD3D9::getFullScreenFlag()
{
    mut.lock();
    bool f = fullScreenFlag;
    mut.unlock();
    return f;
}

void VideoD3D9::showFullScreenD3D9()
{
    bool f = getFullScreenFlag();
    emit showFullScreenD3D9Now(d3d9Ex, d3d9DeviceEx);
    while(getFullScreenFlag() == f) {}
}

void MultimediaEntry::helpVideoD3D9ShowFullScreen(IDirect3D9Ex* d3d9Ex, IDirect3DDevice9Ex* d3d9DeviceEx)
{
    D3DDISPLAYMODE mode;
    d3d9Ex->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);

    //----------------------------------------------------------------------------

    D3DPRESENT_PARAMETERS d3dpar;
    ZeroMemory(&d3dpar, sizeof(d3dpar));

    d3dpar.Windowed = videoD3D9->getFullScreenFlag() ? TRUE : FALSE;
    d3dpar.hDeviceWindow = (HWND)videoD3D9->winId();
    d3dpar.SwapEffect = flipex_mode ? D3DSWAPEFFECT_FLIPEX : D3DSWAPEFFECT_DISCARD;  //交换效果
    d3dpar.PresentationInterval = D3DPRESENT_INTERVAL_ONE;  //一个垂直同步
    d3dpar.BackBufferFormat = videoD3D9->getFullScreenFlag() ? D3DFMT_UNKNOWN : mode.Format;
    d3dpar.BackBufferCount = 1;
    d3dpar.BackBufferWidth = get_video_w();
    d3dpar.BackBufferHeight = get_video_h();


    qDebug()<<d3d9DeviceEx->Reset(&d3dpar)<<D3DERR_INVALIDCALL;

    bool f = videoD3D9->getFullScreenFlag() ? false : true;
    videoD3D9->setFullScreenFlag(f);
}
