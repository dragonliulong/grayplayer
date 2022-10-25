/*
#include "MultimediaVSDL.h"
#include "MultimediaResource.h"
#include <QWindow>
#include <QResizeEvent>
#include <QDebug>

VideoSDL::VideoSDL(QWidget* parent) : QWidget(parent)
{
    window=NULL;
    renderer=NULL;
    texture=NULL;
    videoW=0;
    videoH=0;
    areaW=0;
    areaH=0;
    resizeFlag=false;

    setUpdatesEnabled(false);
    hide();  //隐藏
}

VideoSDL::~VideoSDL()
{
    if (window) SDL_DestroyWindow(window);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (texture) SDL_DestroyTexture(texture);
    SDL_Quit();
}

void VideoSDL::initSDL(int w, int h)
{
    videoW = w;
    videoH = h;

    SDL_Init(SDL_INIT_VIDEO);  //初始化SDL视频系统

    window = SDL_CreateWindowFrom((void*)winId());
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);   // 硬件渲染 | 垂直同步
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, videoW, videoH);
}

void VideoSDL::prepare(AVFrame* frame)
{
    uint8_t* pixels = NULL;
    int pitch = 0;

    SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch);

    //分配设置swsCtx
    SwsContext* swsCtx = sws_getContext(videoW, videoH, (AVPixelFormat)frame->format,
                                        videoW, videoH, AV_PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);

    //分配frameYUV420
    AVFrame* frameYUV420 = av_frame_alloc();
    av_image_fill_arrays(frameYUV420->data, frameYUV420->linesize, pixels, AV_PIX_FMT_YUV420P, videoW, videoH, 1);

    //填充纹理像素空间
    sws_scale(swsCtx, frame->data, frame->linesize, 0, videoH, frameYUV420->data, frameYUV420->linesize);

    //释放frameYUV420
    av_frame_free(&frameYUV420);

    //释放swsCtx
    sws_freeContext(swsCtx);

    SDL_UnlockTexture(texture);

    SDL_RenderCopy(renderer, texture, nullptr, nullptr);  //拷贝纹理到渲染器
}

void VideoSDL::present()
{
    SDL_RenderPresent(renderer);
}

void VideoSDL::resizeEvent(QResizeEvent*)
{
    QMutexLocker locker(&mut);
    resizeFlag = true;
}

void VideoSDL::resizeSDL()
{
    QMutexLocker locker(&mut);

    //if(!resizeFlag) return;
    if(!parentWidget()) return;
    if(parentWidget()->width() == areaW && parentWidget()->height() == areaH) return;

    areaW = parentWidget()->width();
    areaH = parentWidget()->height();

    //刷新渲染器
    //SDL_RenderFlush(renderer);

    //清理渲染器
    //SDL_RenderClear(renderer);

    //--------------------------------------------重置视口-----------------------------------------

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

    SDL_Rect rect;

    rect.x = (areaW - targetW) / 2;
    rect.y = (areaH - targetH) / 2;
    rect.w = targetW;
    rect.h = targetH;

    SDL_RenderSetViewport(renderer, &rect);
    resizeFlag = false;
}

*/

//videoSDL
VideoSDL* videoSDL=NULL;
