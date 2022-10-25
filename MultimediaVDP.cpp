#include "MultimediaVDP.h"
#include "MultimediaHW.h"
#include "MultimediaAddSetting.h"
#include "MultimediaDecodeSetting.h"
#include "MultimediaEvent.h"
#include "MultimediaVD3D9.h"
#include "MultimediaVD3D11.h"

VideoDecoderPlayer::VideoDecoderPlayer()
{
    thread=new QThread();
    this->moveToThread(thread);
    thread->start();
    connect(this,&VideoDecoderPlayer::startDecodePlay,this,&VideoDecoderPlayer::decodePlay);

    videoTimer = new VideoTimer();
    connect(this,&VideoDecoderPlayer::timerStart,videoTimer,&VideoTimer::start);
    connect(this,&VideoDecoderPlayer::timerStop,videoTimer,&VideoTimer::stop);

    packet=NULL;
    frame=NULL;
}

void VideoDecoderPlayer::init()
{
    time_base = av_q2d(videoFmtCtx->streams[get_video_id()]->time_base);
    time_at = 0;

    packet = av_packet_alloc();
    frame = av_frame_alloc();

    emit startDecodePlay();
}

void VideoDecoderPlayer::decodePlay()
{
    skip=false;
    skip_at=0;
    skip_start_clock=0;
    skip_wait_limit=350;    //350ms

    //开始播放
    bool pause=false;
    bool sliderPress=false;

    int integer_fps = ceil(get_fps());
    int updateTime = ((double)1.0/(double)integer_fps) * 1000;  //ms

    emit timerStart(updateTime);

    //--------------------------设置videoD3D大小并显示------------------------------------

    if(renderMode == D3D9)
    {
        videoD3D9->resizeD3D9();
        videoD3D9->showInUi();
    }
    else
    {
        videoD3D11->resizeD3D11();
        videoD3D11->showInUi();
    }

    //-----------------------------------------------------------------------------------

    while(1)  //解码播放循环, 兼事件循环, 不可长时阻塞
    {
        if(!is_video_play_event_empty())
        {
            MultimediaEvent event = get_video_play_event_front();

            //-----------------------处理事件-------------------------

            switch (event.type)
            {
            case SlIDER_PRESS_EVENT:    //进度条handle按下
                sliderPress=true;
                break;

            case SLIDER_RELEASE_EVENT:   //进度条handle松开
                sliderPress=false;
                break;

            case SKIP_EVENT:    //跳转
                if(!event.can_give_up || !skip)
                {
                    av_seek_frame(videoFmtCtx, -1, event.val * AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);
                    avcodec_flush_buffers(videoCodecCtx);

                    //设置skip参数
                    skip=true;
                    skip_at=event.val;
                    skip_start_clock=av_gettime();
                }

                break;

            case PAUSE_EVENT:   //暂停
                pause = pause ? false:true;
                break;

            case STOP_EVENT:
                goto end;
            }

            //--------------------------------------------------------

            pop_video_play_event();
        }

        //-----------------------------------------------------------------------

        if( (!pause && !sliderPress) || skip )
        {
            if(receiveFrame())
            {
                if(renderMode == D3D9) d3d9Deal();
                else d3d11Deal();
            }
        }
        else if(pause || sliderPress)
        {
            QThread::msleep(getSleepAtPause());
        }

        if(renderMode == D3D9) videoD3D9->resizeD3D9();
        else videoD3D11->resizeD3D11();
    }

end:
    emit timerStop();

    if(renderMode == D3D9) videoD3D9->freeResourceAndHide();
    else videoD3D11->freeResourceAndHide();

    freeResource();
}

void VideoDecoderPlayer::d3d9Deal()
{
    //准备
    videoD3D9->prepare(frame);

    //--------------渲染前休眠----------------

    mut.lock();
    VideoPlayerWaiter.wait(&mut);
    mut.unlock();

    //---------------------------------------

    //渲染
    videoD3D9->present();

    //设置video时间
    set_video_time(time_at);
    set_video_clock(av_gettime());
}

void VideoDecoderPlayer::d3d11Deal()
{
    if(videoD3D11->existDataInCurSwapChain())
    {
        //------------渲染前休眠-------------

        mut.lock();
        VideoPlayerWaiter.wait(&mut);
        mut.unlock();

        //----------------------------------

        //渲染
        videoD3D11->present();

        //设置video时间
        set_video_time(time_at);
        set_video_clock(av_gettime());
    }

    //准备并即可转到下一个交换链
    videoD3D11->prepare(frame);
    videoD3D11->turnToNextSwapChain();
}

bool VideoDecoderPlayer::receiveFrame()
{
    bool success = false;

    if(av_read_frame(videoFmtCtx, packet) >= 0)
    {
        if(packet->stream_index == get_video_id())
        {
            avcodec_send_packet(videoCodecCtx, packet);

            if(avcodec_receive_frame(videoCodecCtx, frame) == 0)
            {
                time_at = time_base * frame->best_effort_timestamp;
                int past = (av_gettime() - skip_start_clock) / 1000;

                if( !( skip && time_at < skip_at && past < skip_wait_limit ) && ( skip || isAVSync()) )
                {
                    success = true;
                    skip = false; //重置skip标志
                }
            }
        }

        //重置packet
        av_packet_unref(packet);
    }

    return success;
}

bool VideoDecoderPlayer::isAVSync()
{
    //先判断 要不要进行音视频同步
    if(!isHWSync()) return true;

    int audioPast = (av_gettime() - get_audio_clock()) / 1000;
    int videoPast = (av_gettime() - get_video_clock()) / 1000;

    int current_audio_time = get_audio_time() * 1000 + audioPast;
    int current_video_time = get_video_time() * 1000 + videoPast;

    const int dif = current_video_time - current_audio_time;

    //-------------------------------------------------------------------------------

    if(dif >= 80)   //视频快
    {
        double coef = 0.2;   //等待系数 = 0.2
        int maxWaitTime = 40;  //一次性最大等待时间40ms ( 可以及时处理事件 )
        int waitTime = min( (int)(dif* coef), maxWaitTime);
        if(waitTime > 0) QThread::msleep( waitTime );
    }

    if(dif <= -80)   //视频慢
    {
        if(time_at * 1000 < current_audio_time)
            return false;
    }

    return true;
}

void VideoDecoderPlayer::freeResource()
{
    av_packet_free(&packet);
    av_frame_free(&frame);

    packet=NULL;
    frame=NULL;

    emit endFinish();
}
