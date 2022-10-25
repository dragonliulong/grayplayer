#ifndef MULTIMEDIAVD3D9_H
#define MULTIMEDIAVD3D9_H

#include <QWidget>
#include <windows.h>
#include <initguid.h>
#include <d3d9.h>
#include <dxvahd.h>
#include "MultimediaDXVAHD.h"
#include <MultimediaHW.h>
#include "MultimediaFilter.h"
#include <QLibrary>
#include <QDebug>

typedef void* DXVAHD_HANDLE;

typedef HRESULT (*DXVAHD_CreateDevice_FUN)(IDirect3DDevice9Ex* device, const void* desc, UINT usage, void* plugin, void** pHDDevice);
typedef HRESULT (*HD_GetVideoProcessorDeviceCaps_FUN)(void* device, void* caps);
typedef HRESULT (*HD_GetVideoProcessorCaps_FUN)(void* device, INT count, void* caps);
typedef HRESULT (*HD_GetVideoProcessorFilterRange_FUN)(void* device, UINT filter, void* range);
typedef HRESULT (*HD_CreateVideoProcessor_FUN)(void* device, const GUID* guid, void** pVideoProcessor);
typedef HRESULT (*HD_GetVideoProcessStreamState_FUN)(void* processor, UINT streamId, UINT state, UINT dataSize, void* data);
typedef HRESULT (*HD_SetVideoProcessStreamState_FUN)(void* processor, UINT streamId, UINT state, UINT dataSize, const void* data);
typedef HRESULT (*HD_SetVideoProcessBltState_FUN)(void* processor, UINT state, UINT dataSize, const void* data);
typedef HRESULT (*HD_VideoProcessBltHD_FUN)(void* processor, IDirect3DSurface9 * target, UINT outFrame, UINT streamCount, const void* data);
typedef ULONG (*HD_DeviceRelease_FUN)(void* device);
typedef ULONG (*HD_ProcessorRelease_FUN)(void* processor);

class VideoD3D9 : public QWidget
{
    Q_OBJECT

public:
    VideoD3D9(QWidget* parent=0);

public:
    void initD3D9(int,int);
    void dxva2_device_create(AVCodecContext*);
    void freeResourceAndHide();
    void showInUi();

public:
    void prepare(AVFrame*);
    void present();
    void resizeD3D9();

private:
    void prepareSurface(AVFrame*);
    void prepareYUV(AVFrame*);

private:
    IDirect3D9Ex* d3d9Ex;
    IDirect3DDevice9Ex* d3d9DeviceEx;
    IDirect3DDeviceManager9* d3d9DeviceManager;
    UINT resetToken;

private:
    DXVAHD_HANDLE hd_device;
    DXVAHD_HANDLE hd_processor;

private:
    DXVAHD_CreateDevice_FUN             DXVAHD_CreateDevice;
    HD_GetVideoProcessorDeviceCaps_FUN  HD_GetVideoProcessorDeviceCaps;
    HD_GetVideoProcessorCaps_FUN        HD_GetVideoProcessorCaps;
    HD_GetVideoProcessorFilterRange_FUN HD_GetVideoProcessorFilterRange;
    HD_CreateVideoProcessor_FUN         HD_CreateVideoProcessor;
    HD_GetVideoProcessStreamState_FUN   HD_GetVideoProcessStreamState;
    HD_SetVideoProcessStreamState_FUN   HD_SetVideoProcessStreamState;
    HD_SetVideoProcessBltState_FUN      HD_SetVideoProcessBltState;
    HD_VideoProcessBltHD_FUN            HD_VideoProcessBltHD;
    HD_DeviceRelease_FUN                HD_DeviceRelease;
    HD_ProcessorRelease_FUN             HD_ProcessorRelease;

signals:
    void showFilterNow();
    void hideFilterNow();
    void showInUiNow();
    void hideInUiNow();

private:
    void getDXVAHDFunctions();
    void filterSrcToDst(IDirect3DSurface9* src, IDirect3DSurface9* dst);
    void createVideoProcessor();

private:
    int videoW, videoH;
    int areaW, areaH;

protected:
    QPaintEngine* paintEngine() const { return NULL; }
};

extern VideoD3D9* videoD3D9;

#endif // MULTIMEDIAVD3D9_H
