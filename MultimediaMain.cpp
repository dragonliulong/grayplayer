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

    //??????audioHelper
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

    avformat_close_input(&fmtCtx);  //?????????
    avformat_free_context(fmtCtx);  //??????

    //-----------------------------------------------------------------------------------

    //??????
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
        if(get_multimedia_type() == AUDIO_TYPE) //??????????????????????????????????????????????????????
            audioHelper->setImage(file);

        if(get_multimedia_type() == VIDEO_TYPE || get_multimedia_type() == NETWORK_TYPE)  //????????????????????? ??????/?????? ????????????????????????????????????
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

                //????????????????????????
                switch (renderMode)
                {
                case D3D9:
                    videoD3D9->initD3D9(get_video_w(), get_video_h());
                    break;

                case D3D11:
                    videoD3D11->initD3D11(get_video_w(), get_video_h());
                    break;
                }

                //????????????????????? (??????????????????????????????)
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

                //???????????????
                avcodec_open2(videoCodecCtx, videoCodec, NULL);

                //???????????????????????????
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
    else if(get_multimedia_type() == AUDIO_TYPE) //??????????????????????????????????????????????????????audioHelper
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
    //?????????swrCtx
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

    while(1)  //?????????????????? (????????????????????????????????????)
    {
        if(!is_audio_decode_event_empty())
        {
            MultimediaEvent event=get_audio_decode_event_front();

            if(event.type == SKIP_EVENT)
            {
                //??????
                av_seek_frame(audioFmtCtx, -1, event.val * AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);
                avcodec_flush_buffers(audioCodecCtx);

                //??????skip??????
                skip=true;
                skip_at=event.val;
                skip_start_clock=av_gettime();
            }

            if(event.type == STOP_EVENT)
                break;

            pop_audio_decode_event();
        }

        //??????
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
                        //----------------????????????-------------

                        uint8_t* buffer = (uint8_t*)av_malloc(MAX_PCM_BUFFER_SIZE);  //????????????pcm??????
                        swr_convert(swrCtx, &buffer, MAX_PCM_BUFFER_SIZE, (const uint8_t **)frame->data, frame->nb_samples);
                        //????????????????????????????????? = ????????? * ?????????????????????????????? * ????????????????????????
                        int buffer_size=frame->channels * frame->nb_samples * av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);

                        //----------------????????????-------------

                        bool skip_first=false;

                        if(skip)
                        {
                            skip_first=true;

                            //??????skip??????
                            skip=false;
                        }

                        //??????pcm??????
                        push_pcm(PCM{ buffer, buffer_size, time_at, skip_first});
                        eof_push = false;
                    }
                }
            }

            //??????packet
            av_packet_unref(packet);
        }
        else if(res == AVERROR_EOF && !eof_push)
        {
            push_pcm(PCM{ NULL, -1, -1, true });
            eof_push = true;
        }

        //----------------------------------??????----------------------------------

        if(eof_push) QThread::msleep(10);

        while(get_pcm_size() >= MAX_QUEUE_SIZE)
            QThread::msleep(1);
    }

    //????????????
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

    while(1)  //?????????????????? (????????????????????????????????????)
    {
        if(!is_video_decode_event_empty())
        {
            MultimediaEvent event=get_video_decode_event_front();

            if(event.type == SKIP_EVENT)
            {
                //??????
                av_seek_frame(videoFmtCtx, -1, event.val * AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);
                avcodec_flush_buffers(videoCodecCtx);

                //??????skip??????
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

                            //??????skip??????
                            skip=false;
                        }

                        //??????yuv??????
                        push_yuv(YUV{ frame, time_at, skip_first });
                    }
                    else av_frame_free(&frame); //??????????????????????????????
                }
            }

            //??????packet
            av_packet_unref(packet);
        }

        //--------------------------??????----------------------------------

        while(get_yuv_size() >= MAX_QUEUE_SIZE)
            QThread::msleep(1);
    }

    //????????????
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

    QAudioFormat audioFormat; //??????fmt???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
    audioFormat.setSampleRate(audioCodecCtx->sample_rate);  //????????????????????????
    audioFormat.setSampleSize(16);     //???????????????????????????
    audioFormat.setChannelCount(audioCodecCtx->channels); //????????????????????????
    audioFormat.setCodec("audio/pcm"); //????????????PCM??????
    audioFormat.setByteOrder(QAudioFormat::LittleEndian); //???????????????????????????????????????????????????
    audioFormat.setSampleType(QAudioFormat::SignedInt); //AV_SAMPLE_FMT_S16 ??? signed 16 bits
    audioOut = new QAudioOutput(audioFormat);    //??????QAudioOutput??????????????????
    audioOut->setBufferSize(2 * MB);  //?????????????????????2MB
    audioDevice = audioOut->start(); //??????start??????????????????QIODevice???????????????

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
    //????????????
    bool pause=false;
    bool skip=false;
    bool sliderPress=false;

    proSliderTimer.setUpdateTime(1000);
    emit proSliderTimerStart();

    while(1)  //?????????????????? (???????????????, ??????????????????)
    {
        if(!is_audio_play_event_empty())
        {
            MultimediaEvent event=get_audio_play_event_front();

            //-----------------------????????????-------------------------

            switch (event.type)
            {
            case SlIDER_PRESS_EVENT:   //?????????handle??????
                sliderPress=true;
                emit proSliderTimerStop();
                waitProSliderTimerStop();  //???????????????timer??????
                break;

            case SLIDER_RELEASE_EVENT:   //?????????handle??????
                sliderPress=false;
                emit proSliderTimerStart();   //?????????????????????timer??????
                break;

            case SKIP_EVENT:   //??????
                if(!event.can_give_up || !skip)
                {
                    clear_pcm();

                    if(proSliderTimer.isRunning())
                    {
                        emit proSliderTimerStop();
                        waitProSliderTimerStop();  //???????????????timer??????
                    }

                    push_audio_decode_event(event);
                    skip=true;
                }

                break;

            case PAUSE_EVENT:   //??????
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
                        //----------------------???????????????????????????-------------------------

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

                        //??????audio??????
                        set_audio_time(pcm.time_at);
                        set_audio_clock(av_gettime());

                        if(!proSliderTimer.isRunning() && !sliderPress)
                        {
                            proSliderTimer.helpSetVal();
                            emit proSliderTimerStart();
                        }

                        //??????skip??????
                        skip = false;
                    }
                    else
                    {
                        emit eof();
                    }
                }

                //????????????, ????????????buffer
                pop_pcm();
            }
        }
        else if(pause || sliderPress)
        {
            QThread::msleep(getSleepAtPause());
        }

        //???????????????, ???resizeHelper
        if(get_multimedia_type() == AUDIO_TYPE)
            audioHelper->resizeHelper();

        //????????????
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
    //????????????
    bool pause=false;
    bool skip=false;
    bool sliderPress=false;

    int integer_fps = ceil(get_fps());
    int updateTime = ((double)1.0/(double)integer_fps) * 1000;  //ms

    emit timerStart(updateTime);

    //----------------??????videoD3D9???????????????------------------------

    videoD3D9->resizeD3D9();
    videoD3D9->show();

    //------------------------------------------------------------

    while(1)  //?????????????????? (???????????????, ??????????????????)
    {
        if(!is_video_play_event_empty())
        {
            MultimediaEvent event=get_video_play_event_front();

            //-----------------------????????????-------------------------

            switch (event.type)
            {
            case SlIDER_PRESS_EVENT:    //?????????handle??????
                sliderPress=true;
                break;

            case SLIDER_RELEASE_EVENT:   //?????????handle??????
                sliderPress=false;
                break;

            case SKIP_EVENT:    //??????
                if(!event.can_give_up || !skip)
                {
                    clear_yuv();
                    push_video_decode_event(event);
                    skip=true;
                }

                break;

            case PAUSE_EVENT:   //??????
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
                    //??????????????????
                    videoD3D9->prepare(yuv.frame);

                    //------------------------???????????????------------------------

                    mut.lock();
                    VideoPlayerWaiter.wait(&mut);
                    mut.unlock();

                    //------------------------------------------------------------

                    //??????
                    videoD3D9->present();

                    //??????video??????
                    set_video_time(yuv.time_at);
                    set_video_clock(av_gettime());

                    skip=false;  //??????skip??????
                    sync();  //???????????????
                }

                //????????????, ????????????frame
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

    if(dif >= 80)   //?????????
    {
        double coef = 0.2;   //???????????? = 0.2
        int maxWaitTime = 40;  //???????????????????????????40ms ( ???????????????????????? )
        int waitTime = min( (int)(dif* coef), maxWaitTime);
        if(waitTime > 0) QThread::msleep( waitTime );
    }

    if(dif <= -80)   //?????????
    {
        int lose_limit=3;    //??????????????????3???

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
