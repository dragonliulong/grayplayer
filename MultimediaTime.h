#ifndef MULTIMEDIATIME_H
#define MULTIMEDIATIME_H

#include <QObject>
#include <QSlider>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>

extern "C"
{
    #include <libavutil/time.h>
}

//-----------------------------------------------------------------------------------------

extern const int MAX_QUEUE_SIZE;
extern QWaitCondition VideoPlayerWaiter;

double get_audio_time();
void set_audio_time(double);
uint64_t get_audio_clock();
void set_audio_clock(uint64_t);

double get_video_time();
void set_video_time(double);
uint64_t get_video_clock();
void set_video_clock(uint64_t);

double get_total_time();
void set_total_time(double);

void initProSliderTimer(QSlider* slider);

class ProSliderTimer : public QObject
{
    Q_OBJECT

public:
    ProSliderTimer();

public slots:
    void init(QSlider* slider);
    bool isRunning();
    void helpSetVal();
    void setUpdateTime(int);
    void start();
    void stop();
    void timeoutEvent();

private:
    QSlider* slider;
    QThread* thread;
    QTimer* timer;
};

class VideoTimer : public QObject
{
    Q_OBJECT

public:
    VideoTimer();

public slots:
    void start(int);
    void stop();
    void timeoutEvent();

private:
    QThread* thread;
    QTimer* timer;
};

extern ProSliderTimer proSliderTimer;

#endif // MULTIMEDIATIME_H
