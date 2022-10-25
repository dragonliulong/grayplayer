#include "MultimediaResource.h"
#include "MultimediaInterrupt.h"

AVFormatContext* audioFmtCtx=NULL;
AVFormatContext* videoFmtCtx=NULL;
AVCodecContext* audioCodecCtx=NULL;
AVCodec* audioCodec=NULL;
AVCodecContext* videoCodecCtx=NULL;
AVCodec* videoCodec=NULL;
int audioID=-1;
int videoID=-1;
int video_w=0;
int video_h=0;
double fps=1;
queue<PCM> pcm_queue;
queue<YUV> yuv_queue;

QMutex pcm_mut;
QMutex yuv_mut;
QMutex audio_id_mut;
QMutex video_id_mut;
QMutex fps_mut;
QMutex video_w_mut;
QMutex video_h_mut;

AVFormatContext* GetFormatCtx(const char* file, AVDictionary** opts)
{
    AVFormatContext* AVFormatCtx = avformat_alloc_context(); //描述多媒体文件的构成及其基本信息
    get_interrupt_for(AVFormatCtx);

    if (avformat_open_input(&AVFormatCtx, file, NULL, opts) != 0)
    {
        avformat_close_input(&AVFormatCtx);  //关闭流
        avformat_free_context(AVFormatCtx);  //释放
        return NULL;
    }

    if (avformat_find_stream_info(AVFormatCtx, opts) < 0)
    {
        avformat_close_input(&AVFormatCtx);  //关闭流
        avformat_free_context(AVFormatCtx);  //释放
        return NULL;
    }

    return AVFormatCtx;
}

int FindStreamId(AVFormatContext* AVFormatCtx,AVMediaType type)
{
    for (int i = 0; i < (int)AVFormatCtx->nb_streams; i++)
        if (AVFormatCtx->streams[i]->codecpar->codec_type == type) return i;

    return -1;
}

//-----------------------------------------------------------------------------------------------------

int get_audio_id()
{
    audio_id_mut.lock();
    int x=audioID;
    audio_id_mut.unlock();
    return x;
}

void set_audio_id(int x)
{
    audio_id_mut.lock();
    audioID=x;
    audio_id_mut.unlock();
}

int get_video_id()
{
    video_id_mut.lock();
    int x=videoID;
    video_id_mut.unlock();
    return x;
}

void set_video_id(int x)
{
    video_id_mut.lock();
    videoID=x;
    video_id_mut.unlock();
}

double get_fps()
{
    fps_mut.lock();
    double x=fps;
    fps_mut.unlock();
    return x;
}

void set_fps(double x)
{
    fps_mut.lock();
    fps=x;
    fps_mut.unlock();
}

int get_video_w()
{
    video_w_mut.lock();
    int x=video_w;
    video_w_mut.unlock();
    return x;
}

void set_video_w(int x)
{
    video_w_mut.lock();
    video_w=x;
    video_w_mut.unlock();
}

int get_video_h()
{
    video_h_mut.lock();
    int x=video_h;
    video_h_mut.unlock();
    return x;
}

void set_video_h(int x)
{
    video_h_mut.lock();
    video_h=x;
    video_h_mut.unlock();
}

//------------------------------------------------------------------------------------------------------

bool is_pcm_empty()
{
    pcm_mut.lock();
    bool x=pcm_queue.empty();
    pcm_mut.unlock();
    return x;
}

int get_pcm_size()
{
    pcm_mut.lock();
    int x=pcm_queue.size();
    pcm_mut.unlock();
    return x;
}

PCM get_pcm_front()
{
    pcm_mut.lock();
    PCM pcm={NULL,0,0,false};
    if(!pcm_queue.empty()) pcm=pcm_queue.front();
    pcm_mut.unlock();
    return pcm;
}

void push_pcm(PCM pcm)
{
    pcm_mut.lock();
    pcm_queue.push(pcm);
    pcm_mut.unlock();
}

void pop_pcm()
{
    pcm_mut.lock();

    if(!pcm_queue.empty())
    {
        av_free(pcm_queue.front().buffer);
        pcm_queue.pop();
    }

    pcm_mut.unlock();
}

void clear_pcm()
{
    pcm_mut.lock();

    while(!pcm_queue.empty())
    {
        av_free(pcm_queue.front().buffer);
        pcm_queue.pop();
    }

    pcm_mut.unlock();
}

//----------------------------------------------------------------------------------

bool is_yuv_empty()
{
    yuv_mut.lock();
    bool x=yuv_queue.empty();
    yuv_mut.unlock();
    return x;
}

int get_yuv_size()
{
    yuv_mut.lock();
    int x=yuv_queue.size();
    yuv_mut.unlock();
    return x;
}

YUV get_yuv_front()
{
    yuv_mut.lock();
    YUV yuv={NULL,0,false};
    if(!yuv_queue.empty()) yuv=yuv_queue.front();
    yuv_mut.unlock();
    return yuv;
}

void push_yuv(YUV yuv)
{
    yuv_mut.lock();
    yuv_queue.push(yuv);
    yuv_mut.unlock();
}

void pop_yuv()
{
    yuv_mut.lock();

    if(!yuv_queue.empty())
    {
        av_frame_free(&yuv_queue.front().frame);
        yuv_queue.pop();
    }

    yuv_mut.unlock();
}

void clear_yuv()
{
    yuv_mut.lock();

    while(!yuv_queue.empty())
    {
        av_frame_free(&yuv_queue.front().frame);
        yuv_queue.pop();
    }

    yuv_mut.unlock();
}
