#ifndef MULTIMEDIARESOURCE_H
#define MULTIMEDIARESOURCE_H

#include <QDebug>
#include <QObject>
#include <QAudioOutput>
#include <queue>
#include <QMutex>
#include <QSlider>

using namespace std;

extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavdevice/avdevice.h>
    #include <libavformat/version.h>
    #include <libavutil/time.h>
    #include <libavutil/avassert.h>
    #include <libavutil/mathematics.h>
    #include <libavutil/pixfmt.h>
    #include <libavutil/mem.h>
    #include <libswresample/swresample.h>
    #include <libswresample/version.h>
    #include <libswscale/swscale.h>
    #include <libswscale/version.h>
    #include <libavutil/imgutils.h>
    #include <stdio.h>
}

struct PCM
{
    uint8_t* buffer;
    int buffer_size;
    double time_at;
    bool skip_first;
};

struct YUV
{
    AVFrame* frame;
    double time_at;
    bool skip_first;
};

extern AVFormatContext* audioFmtCtx;
extern AVFormatContext* videoFmtCtx;
extern AVCodecContext* audioCodecCtx;
extern AVCodec* audioCodec;
extern AVCodecContext* videoCodecCtx;
extern AVCodec* videoCodec;

AVFormatContext* GetFormatCtx(const char* file, AVDictionary** opts = NULL);
int FindStreamId(AVFormatContext* AVFormatCtx,AVMediaType type);

//-----------------------------------

int get_audio_id();
void set_audio_id(int);
int get_video_id();
void set_video_id(int);

double get_fps();
void set_fps(double);

int get_video_w();
void set_video_w(int);
int get_video_h();
void set_video_h(int);

//------------------------------------

bool is_pcm_empty();
int get_pcm_size();
PCM get_pcm_front();
void push_pcm(PCM);
void pop_pcm();
void clear_pcm();

//------------------------------------

bool is_yuv_empty();
int get_yuv_size();
YUV get_yuv_front();
void push_yuv(YUV);
void pop_yuv();
void clear_yuv();

#endif // MULTIMEDIARESOURCE_H
