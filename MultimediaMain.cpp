#include "MultimediaMain.h"
#include "MultimediaDecodeSetting.h"
#include "MultimediaAddSetting.h"
#include "MultimediaAHelper.h"
#include "MultimediaType.h"
#include "MultimediaExit.h"
#include <QFileInfo>
#include "cmath"

MultimediaEntry::MultimediaEntry()
{
    interrupter = new Interrupter();
    thread=new QThread();
    this->moveToThread(thread);
    thread->start();
}

Interrupter* MultimediaEntry::getInterrupter()
{
    return interrupter;
}

void MultimediaEntry::sliderPress()
{
    if(get_audio_id() != -1)
        push_audio_play_event({SlIDER_PRESS_EVENT,0,false});

    if(get_video_id() != -1 && (get_multimedia_type() == VIDEO_TYPE || get_multimedia_type() == NETWORK_TYPE))
        push_video_play_event({SlIDER_PRESS_EVENT,0,false});
}

void MultimediaEntry::sliderRelease()
{
    if(get_audio_id() != -1)
        push_audio_play_event({SLIDER_RELEASE_EVENT,0,false});

    if(get_video_id() != -1 && (get_multimedia_type() == VIDEO_TYPE || get_multimedia_type() == NETWORK_TYPE))
        push_video_play_event({SLIDER_RELEASE_EVENT,0,false});
}

void MultimediaEntry::skip(double per, bool can_give_up)
{
    double t = per * get_total_time();

    if(get_audio_id() != -1)
        push_audio_play_event({SKIP_EVENT,t,can_give_up});

    if(get_video_id() != -1 && (get_multimedia_type() == VIDEO_TYPE || get_multimedia_type() == NETWORK_TYPE))
        push_video_play_event({SKIP_EVENT,t,can_give_up});
}

void MultimediaEntry::pause()
{
    if(get_audio_id() != -1)
        push_audio_play_event({PAUSE_EVENT,0,false});

    if(get_video_id() != -1 && (get_multimedia_type() == VIDEO_TYPE || get_multimedia_type() == NETWORK_TYPE))
        push_video_play_event({PAUSE_EVENT,0,false});
}

void MultimediaEntry::stop(int flag)
{
    stopObjectFlag = flag;
    bool beh = false;

    if(get_multimedia_type() != UNKNOW_TYPE)
    {
        push_audio_play_event({STOP_EVENT,0,false});
        beh = true;
    }

    if(get_multimedia_type() == VIDEO_TYPE || get_multimedia_type() == NETWORK_TYPE)
    {
        push_video_play_event({STOP_EVENT,0,false});
        beh = true;
    }

    if(!beh) stopFinish();
}

void MultimediaEntry::stopFinish(bool e)
{
    MultimediaType type = UNKNOW_TYPE;
    set_multimedia_type((char*)"", &type);
    set_interrupt_flag(false);
    set_exit_flag(true);
    if(e) emit stopFinishNow(stopObjectFlag);
}

void MultimediaEntry::setVideoShowAt(QWidget* w)
{
    switch (renderMode)
    {
    case D3D9:
        videoD3D9 = new VideoD3D9(w);
        break;

    case D3D11:
        videoD3D11 = new VideoD3D11(w);
        break;
    }

    //创建audioHelper
    audioHelper = new AudioHelper(w);
}

void MultimediaEntry::clearForPrepare()
{
    while(!is_audio_decode_event_empty())
        pop_audio_decode_event();

    while(!is_video_decode_event_empty())
        pop_video_decode_event();

    clear_pcm();
    clear_yuv();
}

void MultimediaEntry::open(char* file)
{
    set_interrupt_flag(false);

    //-----------------------------------------------------------------------------------

    AVFormatContext* fmtCtx = GetFormatCtx(file);

    if(fmtCtx == NULL)
    {
        stopFinish(false);
        emit openFail(-1);
        return;
    }

    set_multimedia_type(file, NULL);
    set_audio_id(FindStreamId(fmtCtx, AVMEDIA_TYPE_AUDIO));
    set_video_id(FindStreamId(fmtCtx, AVMEDIA_TYPE_VIDEO));
    set_total_time(fmtCtx->duration/(double)AV_TIME_BASE);
    emit totalTimeChange(get_total_time());

    avformat_close_input(&fmtCtx);  //关闭流
    avformat_free_context(fmtCtx);  //释放

    //-----------------------------------------------------------------------------------

    //清理
    clearForPrepare();
    callCount = 0;

    if(get_audio_id() != -1)
    {
        audioFmtCtx = GetFormatCtx(file);

        if(audioFmtCtx)
        {
            audioCodec = avcodec_find_decoder(audioFmtCtx->streams[get_audio_id()]->codecpar->codec_id);
            audioCodecCtx = avcodec_alloc_context3(audioCodec);
            audioCodecCtx->pkt_timebase = audioFmtCtx->streams[get_audio_id()]->time_base;
            avcodec_parameters_to_context(audioCodecCtx, audioFmtCtx->streams[get_audio_id()]->codecpar);
            avcodec_open2(audioCodecCtx, audioCodec, NULL);

            emit callAudioDecoder(); callCount++;
            emit callAudioPlayer(); callCount++;
        }
    }

    if(get_video_id() != -1)
    {
        if(get_multimedia_type() == AUDIO_TYPE) //有视频流，且是音频文件，则判断是封面
            audioHelper->setImage(file);

        if(get_multimedia_type() == VIDEO_TYPE || get_multimedia_type() == NETWORK_TYPE)  //有视频流，且是 视频/网络 文件，则判断应该渲染视频
        {
            videoFmtCtx = GetFormatCtx(file);

            if(videoFmtCtx)
            {
                //---------------------------------------------------------

                set_fps(av_q2d(videoFmtCtx->streams[get_video_id()]->avg_frame_rate));
                set_video_w(videoFmtCtx->streams[get_video_id()]->codecpar->width);
                set_video_h(videoFmtCtx->streams[get_video_id()]->codecpar->height);

                //---------------------------------------------------------

                videoCodec = avcodec_find_decoder(videoFmtCtx->streams[get_video_id()]->codecpar->codec_id);
                videoCodecCtx = avcodec_alloc_context3(videoCodec);
                videoCodecCtx->pkt_timebase = videoFmtCtx->streams[get_video_id()]->time_base;
                avcodec_parameters_to_context(videoCodecCtx, videoFmtCtx->streams[get_video_id()]->codecpar);

                //初始化视频渲染器
                switch (renderMode)
                {
                case D3D9:
                    videoD3D9->initD3D9(get_video_w(), get_video_h());
                    break;

                case D3D11:
                    videoD3D11->initD3D11(get_video_w(), get_video_h());
                    break;
                }

                //获取硬件解码器 (软解则使用多线程解码)
                switch (decodeMode)
                {
                case DXVA2:
                    get_hw_decoder(videoCodecCtx, videoCodec, HW_DXVA2);
                    break;

                case D3D11VA:
                    get_hw_decoder(videoCodecCtx, videoCodec, HW_D3D11VA);
                    break;

                case SOFTWARE:
                    videoCodecCtx->thread_count = sw_thread_count;
                    break;
                }

                //打开解码器
                avcodec_open2(videoCodecCtx, videoCodec, NULL);

                //发信号开始解码渲染
                switch (decodeMode)
                {
                case SOFTWARE:
                    emit callVideoDecoder(); callCount++;
                    emit callVideoPlayer(); callCount++;
                    break;

                default:
                    emit callVideoDecoderPlayer(); callCount++;
                    break;
                }
            }
        }
    }
    else if(get_multimedia_type() == AUDIO_TYPE) //没有视频流，但是是音频文件，还是显示audioHelper
    {
        audioHelper->setImage(NULL);
    }

    if(callCount <= 0)
    {
        stopFinish(false);
        emit openFail(-1);
    }
}

void MultimediaEntry::subAndCheckCallCount()
{
    callCount--;
    if(callCount <= 0) stopFinish();
}

void MultimediaEntry::audioDecoderClear()
{
    while(!is_audio_decode_event_empty())
        pop_audio_decode_event();

    avformat_close_input(&audioFmtCtx);
    avformat_free_context(audioFmtCtx);
    avcodec_free_context(&audioCodecCtx);

    audioFmtCtx=NULL;
    audioCodecCtx=NULL;
    audioCodec=NULL;

    set_audio_id(-1);

    subAndCheckCallCount();
}

void MultimediaEntry::audioPlayerClear()
{
    while(!is_audio_play_event_empty())
        pop_audio_play_event();

    clear_pcm();

    set_audio_time(0);
    set_audio_clock(0);

    subAndCheckCallCount();
}

void MultimediaEntry::videoDecoderClear()
{
    while(!is_video_decode_event_empty())
        pop_video_decode_event();

    avformat_close_input(&videoFmtCtx);
    avformat_free_context(videoFmtCtx);
    avcodec_free_context(&videoCodecCtx);

    videoFmtCtx=NULL;
    videoCodecCtx=NULL;
    videoCodec=NULL;

    set_video_id(-1);

    subAndCheckCallCount();
}

void MultimediaEntry::videoPlayerClear()
{
    while(!is_video_play_event_empty())
        pop_video_play_event();

    clear_yuv();

    set_video_time(0);
    set_video_clock(0);

    subAndCheckCallCount();
}

void MultimediaEntry::videoDecoderPlayerClear()
{
    while(!is_video_play_event_empty())
        pop_video_play_event();

    avformat_close_input(&videoFmtCtx);
    avformat_free_context(videoFmtCtx);
    avcodec_free_context(&videoCodecCtx);

    videoFmtCtx=NULL;
    videoCodecCtx=NULL;
    videoCodec=NULL;

    set_video_id(-1);
    set_video_time(0);
    set_video_clock(0);

    subAndCheckCallCount();
}

//---------------------------------------------------AudioDecoder----------------------------------------------

AudioDecoder::AudioDecoder()
{
    thread=new QThread();
    this->moveToThread(thread);
    thread->start();
    connect(this,&AudioDecoder::startDecode,this,&AudioDecoder::decode);

    packet=NULL;
    frame=NULL;
    swrCtx=NULL;
}

void AudioDecoder::init()
{
    packet = av_packet_alloc();
    frame = av_frame_alloc();

    time_base = av_q2d(audioFmtCtx->streams[get_audio_id()]->time_base);

    swrCtx = swr_alloc();
    swr_alloc_set_opts(swrCtx, audioCodecCtx->channel_layout, AV_SAMPLE_FMT_S16,audioCodecCtx->sample_rate,
                       audioCodecCtx->channel_layout, audioCodecCtx->sample_fmt,audioCodecCtx->sample_rate, 0, NULL);
    //初始化swrCtx
    swr_init(swrCtx);

    emit startDecode();
}

void AudioDecoder::decode()
{
    bool eof_push = false;

    bool skip=false;
    double skip_at=0;
    const int skip_wait_limit=350;    //350ms
    uint64_t skip_start_clock=0;

    while(1)  //音频解码循环 (在队列大小达到最大时阻塞)
    {
        if(!is_audio_decode_event_empty())
        {
            MultimediaEvent event=get_audio_decode_event_front();

            if(event.type == SKIP_EVENT)
            {
                //跳转
                av_seek_frame(audioFmtCtx, -1, event.val * AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);
                avcodec_flush_buffers(audioCodecCtx);

                //设置skip参数
                skip=true;
                skip_at=event.val;
                skip_start_clock=av_gettime();
            }

            if(event.type == STOP_EVENT)
                break;

            pop_audio_decode_event();
        }

        //读取
        int res = av_read_frame(audioFmtCtx, packet);

        if(res >= 0)
        {
            if(packet->stream_index == get_audio_id())
            {
                avcodec_send_packet(audioCodecCtx,packet);

                while(avcodec_receive_frame(audioCodecCtx,frame) == 0)
                {
                    double time_at = time_base * frame->best_effort_timestamp;
                    int past = (av_gettime() - skip_start_clock) / 1000;

                    if( ! ( skip && time_at < skip_at && past < skip_wait_limit) )
                    {
                        //----------------开始任务-------------

                        uint8_t* buffer = (uint8_t*)av_malloc(MAX_PCM_BUFFER_SIZE);  //转换后的pcm数据
                        swr_convert(swrCtx, &buffer, MAX_PCM_BUFFER_SIZE, (const uint8_t **)frame->data, frame->nb_samples);
                        //获取实际占用的缓存大小 = 声道数 * 每个声道输出的样本数 * 每个样本的字节数
                        int buffer_size=frame->channels * frame->nb_samples * av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);

                        //----------------结束任务-------------

                        bool skip_first=false;

                        if(skip)
                        {
                            skip_first=true;

                            //重置skip标志
                            skip=false;
                        }

                        //放入pcm队列
                        push_pcm(PCM{ buffer, buffer_size, time_at, skip_first});
                        eof_push = false;
                    }
                }
            }

            //重置packet
            av_packet_unref(packet);
        }
        else if(res == AVERROR_EOF && !eof_push)
        {
            push_pcm(PCM{ NULL, -1, -1, true });
            eof_push = true;
        }

        //----------------------------------休眠----------------------------------

        if(eof_push) QThread::msleep(10);

        while(get_pcm_size() >= MAX_QUEUE_SIZE)
            QThread::msleep(1);
    }

    //释放资源
    freeResource();
}

void AudioDecoder::freeResource()
{
    av_packet_free(&packet);
    av_frame_free(&frame);
    swr_free(&swrCtx);

    packet=NULL;
    frame=NULL;
    swrCtx=NULL;

    emit endFinish();
}

//--------------------------------------------------------------------------------------------------------------

VideoDecoder::VideoDecoder()
{
    thread=new QThread();
    this->moveToThread(thread);
    thread->start();
    connect(this,&VideoDecoder::startDecode,this,&VideoDecoder::decode);
    packet=NULL;
}

void VideoDecoder::init()
{
    time_base = av_q2d(videoFmtCtx->streams[get_video_id()]->time_base);
    packet = av_packet_alloc();

    emit startDecode();
}

void VideoDecoder::decode()
{
    bool skip=false;
    double skip_at=0;
    uint64_t skip_start_clock=0;
    const int skip_wait_limit=350;    //350ms

    while(1)  //视频解码循环 (在队列大小达到最大时阻塞)
    {
        if(!is_video_decode_event_empty())
        {
            MultimediaEvent event=get_video_decode_event_front();

            if(event.type == SKIP_EVENT)
            {
                //跳转
                av_seek_frame(videoFmtCtx, -1, event.val * AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);
                avcodec_flush_buffers(videoCodecCtx);

                //设置skip参数
                skip=true;
                skip_at=event.val;
                skip_start_clock=av_gettime();
            }

            if(event.type == STOP_EVENT)
                break;

            pop_video_decode_event();
        }

        //-----------------------------------------------------------------------

        if(av_read_frame(videoFmtCtx, packet) >= 0)
        {
            if(packet->stream_index == get_video_id())
            {
                avcodec_send_packet(videoCodecCtx, packet);

                AVFrame* frame = av_frame_alloc();

                if(avcodec_receive_frame(videoCodecCtx, frame) == 0)
                {  
                    double time_at = time_base * frame->best_effort_timestamp;
                    int past = (av_gettime() - skip_start_clock) / 1000;

                    if( ! ( skip && time_at < skip_at && past < skip_wait_limit ) )
                    {
                        bool skip_first=false;

                        if(skip)
                        {
                            skip_first=true;

                            //重置skip标志
                            skip=false;
                        }

                        //放入yuv队列
                        push_yuv(YUV{ frame, time_at, skip_first });
                    }
                    else av_frame_free(&frame); //不放入队列就记得释放
                }
            }

            //重置packet
            av_packet_unref(packet);
        }

        //--------------------------休眠----------------------------------

        while(get_yuv_size() >= MAX_QUEUE_SIZE)
            QThread::msleep(1);
    }

    //释放资源
    freeResource();
}

void VideoDecoder::freeResource()
{
    av_packet_free(&packet);
    packet=NULL;
    emit endFinish();
}

//---------------------------------------------------AudioPlayer---------------------------------------------------

AudioPlayer::AudioPlayer()
{
    thread=new QThread();
    this->moveToThread(thread);
    thread->start();

    connect(this,&AudioPlayer::startPlay,this,&AudioPlayer::play);

    volume=NULL;
    audioOut=NULL;
    audioDevice=NULL;

    audioReleaser = new AudioReleaser();

    connect(this,&AudioPlayer::release,audioReleaser,&AudioReleaser::releaseAudioOutput);
}

void AudioPlayer::init()
{
    int MB = 1024 * 1024;

    QAudioFormat audioFormat; //通过fmt设定音频数据格式。只有明确知道音频数据的声道数、采样率、采样位数，才可以正常地播放
    audioFormat.setSampleRate(audioCodecCtx->sample_rate);  //设定播放的采样率
    audioFormat.setSampleSize(16);     //设定播放的采样位数
    audioFormat.setChannelCount(audioCodecCtx->channels); //设定播放的声道数
    audioFormat.setCodec("audio/pcm"); //设定播放PCM数据
    audioFormat.setByteOrder(QAudioFormat::LittleEndian); //设定字节序，以小端模式播放音频文件
    audioFormat.setSampleType(QAudioFormat::SignedInt); //AV_SAMPLE_FMT_S16 为 signed 16 bits
    audioOut = new QAudioOutput(audioFormat);    //创建QAudioOutput对象并初始化
    audioOut->setBufferSize(2 * MB);  //设置缓冲区大小2MB
    audioDevice = audioOut->start(); //调用start函数后，返回QIODevice对象的地址

    connect(this,&AudioPlayer::proSliderTimerStart,&proSliderTimer,&ProSliderTimer::start);
    connect(this,&AudioPlayer::proSliderTimerStop,&proSliderTimer,&ProSliderTimer::stop);

    emit startPlay();
}

void AudioPlayer::setVolumeSlider(QSlider* s)
{
    volume = s;
}

void AudioPlayer::waitProSliderTimerStop()
{
    while(proSliderTimer.isRunning()) {}
}

void AudioPlayer::play()
{ 
    //开始播放
    bool pause=false;
    bool skip=false;
    bool sliderPress=false;

    proSliderTimer.setUpdateTime(1000);
    emit proSliderTimerStart();

    while(1)  //音频播放循环 (兼事件循环, 不可长时阻塞)
    {
        if(!is_audio_play_event_empty())
        {
            MultimediaEvent event=get_audio_play_event_front();

            //-----------------------处理事件-------------------------

            switch (event.type)
            {
            case SlIDER_PRESS_EVENT:   //进度条handle按下
                sliderPress=true;
                emit proSliderTimerStop();
                waitProSliderTimerStop();  //等待进度条timer停止
                break;

            case SLIDER_RELEASE_EVENT:   //进度条handle松开
                sliderPress=false;
                emit proSliderTimerStart();   //无需等待进度条timer开始
                break;

            case SKIP_EVENT:   //跳转
                if(!event.can_give_up || !skip)
                {
                    clear_pcm();

                    if(proSliderTimer.isRunning())
                    {
                        emit proSliderTimerStop();
                        waitProSliderTimerStop();  //等待进度条timer停止
                    }

                    push_audio_decode_event(event);
                    skip=true;
                }

                break;

            case PAUSE_EVENT:   //暂停
                pause = pause ? false:true;
                break;

            case STOP_EVENT:
                push_audio_decode_event(event);
                goto end;
            }

            //-------------------------------------------------------

            pop_audio_play_event();
        }

        if( ((!pause && !sliderPress) || skip) )
        {
            if(!is_pcm_empty())
            {
                PCM pcm=get_pcm_front();

                if(!skip || pcm.skip_first)
                {
                    if(pcm.buffer)
                    {
                        //----------------------写入音频设备缓冲区-------------------------

                        int remain = pcm.buffer_size;
                        int buffer_at = 0;

                        while(remain > 0)
                        {
                            int writeBytes = min(audioOut->bytesFree(), remain);
                            audioDevice->write((char*)pcm.buffer + buffer_at, writeBytes);
                            remain -= writeBytes;
                            buffer_at += writeBytes;

                            QThread::msleep(1);
                        }

                        //-------------------------------------------------------------

                        //设置audio时间
                        set_audio_time(pcm.time_at);
                        set_audio_clock(av_gettime());

                        if(!proSliderTimer.isRunning() && !sliderPress)
                        {
                            proSliderTimer.helpSetVal();
                            emit proSliderTimerStart();
                        }

                        //重置skip标志
                        skip = false;
                    }
                    else
                    {
                        emit eof();
                    }
                }

                //弹出队头, 内部释放buffer
                pop_pcm();
            }
        }
        else if(pause || sliderPress)
        {
            QThread::msleep(getSleepAtPause());
        }

        //是音频类型, 就resizeHelper
        if(get_multimedia_type() == AUDIO_TYPE)
            audioHelper->resizeHelper();

        //设置音量
        if(volume)
            audioOut->setVolume((double)volume->value() / (double)volume->maximum());
    }

end:
    emit proSliderTimerStop();

    if(get_multimedia_type() == AUDIO_TYPE)
        audioHelper->freeResourceAndHide();

    freeResource();
}

void AudioPlayer::freeResource()
{
    emit release(audioOut);
    audioOut = NULL;
    audioDevice = NULL;

    emit endFinish();
}

//------------------------------------------------------------------------------------------------------------------

VideoPlayer::VideoPlayer()
{
    thread=new QThread();
    this->moveToThread(thread);
    thread->start();
    connect(this,&VideoPlayer::startPlay,this,&VideoPlayer::play);

    videoTimer = new VideoTimer();
    connect(this,&VideoPlayer::timerStart,videoTimer,&VideoTimer::start);
    connect(this,&VideoPlayer::timerStop,videoTimer,&VideoTimer::stop);
}

void VideoPlayer::init()
{
    videoW=get_video_w();
    videoH=get_video_h();

    emit startPlay();
}

void VideoPlayer::play()
{
    //开始播放
    bool pause=false;
    bool skip=false;
    bool sliderPress=false;

    int integer_fps = ceil(get_fps());
    int updateTime = ((double)1.0/(double)integer_fps) * 1000;  //ms

    emit timerStart(updateTime);

    //----------------设置videoD3D9大小并显示------------------------

    videoD3D9->resizeD3D9();
    videoD3D9->show();

    //------------------------------------------------------------

    while(1)  //视频播放循环 (兼事件循环, 不可长时阻塞)
    {
        if(!is_video_play_event_empty())
        {
            MultimediaEvent event=get_video_play_event_front();

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
                    clear_yuv();
                    push_video_decode_event(event);
                    skip=true;
                }

                break;

            case PAUSE_EVENT:   //暂停
                pause = pause ? false:true;
                break;

            case STOP_EVENT:
                push_video_decode_event(event);
                goto end;
            }

            //---------------------------------------------------

            pop_video_play_event();
        }

        //--------------------------------------------------------------------

        if( ((!pause && !sliderPress) || skip) )
        {
            if(!is_yuv_empty())
            {
                YUV yuv=get_yuv_front();

                if(!skip || yuv.skip_first)
                {
                    //为渲染做准备
                    videoD3D9->prepare(yuv.frame);

                    //------------------------渲染前休眠------------------------

                    mut.lock();
                    VideoPlayerWaiter.wait(&mut);
                    mut.unlock();

                    //------------------------------------------------------------

                    //渲染
                    videoD3D9->present();

                    //设置video时间
                    set_video_time(yuv.time_at);
                    set_video_clock(av_gettime());

                    skip=false;  //重置skip标志
                    sync();  //音视频同步
                }

                //弹出队头, 内部释放frame
                pop_yuv();
            }
        }
        else if(pause || sliderPress)
        {
            QThread::msleep(getSleepAtPause());
        }

        videoD3D9->resizeD3D9();
    }

end:
    emit timerStop();
    videoD3D9->freeResourceAndHide();
    freeResource();
}

void VideoPlayer::freeResource()
{
    emit endFinish();
}

void VideoPlayer::sync()
{
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
        int lose_limit=3;    //一次性最多丢3帧

        while(!is_yuv_empty() && get_yuv_front().time_at <= current_audio_time && lose_limit > 0)
        {
            pop_yuv();
            lose_limit--;
        }
    }
}

void MultimediaConnect(MultimediaEntry* ent,AudioDecoder* ad,VideoDecoder* vd,AudioPlayer* ap,VideoPlayer* vp,VideoDecoderPlayer* vdp)
{
    QObject::connect(ent,&MultimediaEntry::callAudioDecoder,ad,&AudioDecoder::init);
    QObject::connect(ent,&MultimediaEntry::callVideoDecoder,vd,&VideoDecoder::init);
    QObject::connect(ent,&MultimediaEntry::callAudioPlayer,ap,&AudioPlayer::init);
    QObject::connect(ent,&MultimediaEntry::callVideoPlayer,vp,&VideoPlayer::init);
    QObject::connect(ent,&MultimediaEntry::callVideoDecoderPlayer,vdp,&VideoDecoderPlayer::init);

    QObject::connect(ad,&AudioDecoder::endFinish,ent,&MultimediaEntry::audioDecoderClear);
    QObject::connect(ap,&AudioPlayer::endFinish,ent,&MultimediaEntry::audioPlayerClear);
    QObject::connect(vd,&VideoDecoder::endFinish,ent,&MultimediaEntry::videoDecoderClear);
    QObject::connect(vp,&VideoPlayer::endFinish,ent,&MultimediaEntry::videoPlayerClear);
    QObject::connect(vdp,&VideoDecoderPlayer::endFinish,ent,&MultimediaEntry::videoDecoderPlayerClear);
}
