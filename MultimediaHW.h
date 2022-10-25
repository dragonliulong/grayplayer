#ifndef MULTIMEDIAHW_H
#define MULTIMEDIAHW_H

extern "C"
{
    #include <libavcodec/avcodec.h>
    #include "libavformat/avio.h"
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavdevice/avdevice.h>
    #include <libavformat/version.h>
    #include <libavutil/time.h>
    #include <libavutil/mathematics.h>
    #include <libavutil/pixfmt.h>
    #include <libavutil/mem.h>
    #include <libswresample/swresample.h>
    #include <libswresample/version.h>
    #include <libswscale/swscale.h>
    #include <libswscale/version.h>

    #include <libavutil/pixdesc.h>
    #include <libavutil/hwcontext.h>
    #include <libavutil/hwcontext_cuda.h>
    #include <libavutil/hwcontext_d3d11va.h>
    #include <libavutil/hwcontext_dxva2.h>
    #include <libavutil/mem.h>
    #include <libavutil/buffer.h>
    #include <libavutil/error.h>
    #include <libavutil/opt.h>
    #include <libavutil/avassert.h>
    #include <libavutil/imgutils.h>
    #include <stdio.h>
}

extern const AVHWDeviceType HW_DXVA2;
extern const AVHWDeviceType HW_D3D11VA;
extern AVHWDeviceType currentHWDeviceType;

bool get_hw_decoder(AVCodecContext*,AVCodec*,const AVHWDeviceType);


#endif // MULTIMEDIAHW_H
