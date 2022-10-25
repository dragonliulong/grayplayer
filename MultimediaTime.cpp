#include "MultimediaTime.h"
#include <QTimerEvent>
#include <QMutex>
#include <QTimer>
#include <QDebug>
#include <windows.h>

const int MAX_QUEUE_SIZE = 20;

ProSliderTimer proSliderTimer;
QWaitCondition VideoPlayerWaiter;

double total_time=0;
double AudioTime=0;
double VideoTime=0;
uint64_t AudioClock=0;
uint64_t VideoClock=0;

QMutex audio_clock_mut;
QMutex video_clock_mut;
QMutex total_time_mut;
QMutex audio_time_mut;
QMutex video_time_mut;

//--------------------------------------------------------------------------------------------------

double get_audio_time()
{
    audio_time_mut.lock();
    double x=AudioTime;
    audio_time_mut.unlock();
    return x;
}

void set_audio_time(double x)
{
    audio_time_mut.lock();
    AudioTime=x;
    audio_time_mut.unlock();
}

double get_video_time()
{
    video_time_mut.lock();
    double x=VideoTime;
    video_time_mut.unlock();
    return x;
}

void set_video_time(double x)
{
    video_time_mut.lock();
    VideoTime=x;
    video_time_mut.unlock();
}

double get_total_time()
{
    total_time_mut.lock();
    double x=total_time;
    total_time_mut.unlock();
    return x;
}

void set_total_time(double x)
{
    total_time_mut.lock();
    total_time=x;
    total_time_mut.unlock();
}

//-------------------------------------------------------------------

uint64_t get_audio_clock()
{
    audio_clock_mut.lock();
    uint64_t x=AudioClock;
    audio_clock_mut.unlock();
    return x;
}

void set_audio_clock(uint64_t x)
{
    audio_clock_mut.lock();
    AudioClock=x;
    audio_clock_mut.unlock();
}

uint64_t get_video_clock()
{
    video_clock_mut.lock();
    uint64_t x=VideoClock;
    video_clock_mut.unlock();
    return x;
}

void set_video_clock(uint64_t x)
{
    video_clock_mut.lock();
    VideoClock=x;
    video_clock_mut.unlock();
}

//-------------------------------------------------------------------------------

void initProSliderTimer(QSlider* slider)
{ proSliderTimer.init(slider); }

ProSliderTimer::ProSliderTimer() {}

void ProSliderTimer::init(QSlider* slider)
{
    this->slider=slider;

    thread=new QThread();
    this->moveToThread(thread);
    thread->start();

    timer=new QTimer();
    timer->moveToThread(thread);
    connect(timer,&QTimer::timeout,this,&ProSliderTimer::timeoutEvent);
}

bool ProSliderTimer::isRunning()
{ return timer->isActive(); }

void ProSliderTimer::setUpdateTime(int x)
{ timer->setInterval(x); }

void ProSliderTimer::start()
{ timer->start(); }

void ProSliderTimer::stop()
{ timer->stop(); }

void ProSliderTimer::helpSetVal()
{
    int val = (get_audio_time()/get_total_time())*slider->maximum();
    slider->setValue(val);
}

void ProSliderTimer::timeoutEvent()
{
    int val = (get_audio_time()/get_total_time())*slider->maximum();
    slider->setValue(val);
}

//------------------------------------------------------------------------------------

VideoTimer::VideoTimer()
{
    thread=new QThread();
    this->moveToThread(thread);
    thread->start();

    timer=new QTimer();
    timer->setTimerType(Qt::PreciseTimer);  //精确的
    timer->moveToThread(thread);
    connect(timer,&QTimer::timeout,this,&VideoTimer::timeoutEvent);
}

void VideoTimer::start(int ms)
{
    timer->start(ms);
}

void VideoTimer::stop()
{
    timer->stop();
}

void VideoTimer::timeoutEvent()
{
    VideoPlayerWaiter.wakeAll();
}
