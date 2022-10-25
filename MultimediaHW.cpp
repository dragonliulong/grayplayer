#include "MultimediaHW.h"
#include "MultimediaVD3D9.h"
#include "MultimediaVD3D11.h"
#include <QDebug>

const AVHWDeviceType HW_DXVA2 = AV_HWDEVICE_TYPE_DXVA2;
const AVHWDeviceType HW_D3D11VA = AV_HWDEVICE_TYPE_D3D11VA;

AVHWDeviceType currentHWDeviceType = AV_HWDEVICE_TYPE_NONE;
AVPixelFormat pixFmt = AV_PIX_FMT_NONE;

//----------------------------------------------------------------------------------------------------

AVPixelFormat get_hw_format(AVCodecContext*, const enum AVPixelFormat* fmt)
{   
    const enum AVPixelFormat* p;

    for(p = fmt; *p != AV_PIX_FMT_NONE; p++)
        if(*p == pixFmt)
            return *p;

    return AV_PIX_FMT_NONE;
}

bool get_hw_decoder(AVCodecContext* codecCtx, AVCodec* codec, const AVHWDeviceType type)
{
    for(int i=0;;i++)
    {
         const AVCodecHWConfig* config = avcodec_get_hw_config(codec,i);

         if(!config)
         {
             currentHWDeviceType = AV_HWDEVICE_TYPE_NONE;
             pixFmt = AV_PIX_FMT_NONE;
             return false;
         }

         if (config->device_type == type)
         {
             currentHWDeviceType = type;
             pixFmt = config->pix_fmt;
             break;
         }
    }

    switch (type)
    {
    case HW_DXVA2:
        videoD3D9->dxva2_device_create(codecCtx);
        break;

    case HW_D3D11VA:
        videoD3D11->d3d11va_device_create(codecCtx);
        break;

    default: break;
    }

    codecCtx->get_format = get_hw_format;

    return true;
}
