#ifndef MULTIMEDIAMAIN_H
#define MULTIMEDIAMAIN_H

#include <QDebug>
#include <QLayout>
#include <QObject>
#include <QPaintEvent>
#include <QThread>
#include <QAudioOutput>
#include <QMutex>
#include <QSlider>
#include <QTimer>
#include <QWaitCondition>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "MultimediaTime.h"
#include "MultimediaVGL.h"
#include "MultimediaVSDL.h"
#include "MultimediaResource.h"
#include "MultimediaEvent.h"
#include "MultimediaVDT.h"
#include "MultimediaAReleaser.h"
#include "MultimediaVD3D9.h"
#include "MultimediaVD3D11.h"
#include "MultimediaHW.h"
#include "MultimediaVDP.h"
#include "MultimediaInterrupt.h"

class MultimediaEntry : public QObject
{
    Q_OBJECT

public:
    MultimediaEntry();
    void setVideoShowAt(QWidget*);
    Interrupter* getInterrupter();

public slots:
    void open(char* file);
    void sliderPress();
    void sliderRelease();
    void skip(double,bool can_give_up=false);
    void stop(int flag=0);
    void pause();

public slots:
    void audioDecoderClear();
    void audioPlayerClear();
    void videoDecoderClear();
    void videoPlayerClear();
    void videoDecoderPlayerClear();

signals:
    void openFail(int);
    void totalTimeChange(double);
    void stopFinishNow(int flag=0);
    void callAudioDecoder();
    void callVideoDecoder();
    void callAudioPlayer();
    void callVideoPlayer();
    void callVideoDecoderPlayer();

private:
    QThread* thread;
    int callCount;
    int stopObjectFlag;
    Interrupter* interrupter;

private:
    void clearForPrepare();
    void subAndCheckCallCount();
    void stopFinish(bool e=true);
};

class AudioDecoder : public QObject
{
    Q_OBJECT

public:
    AudioDecoder();

public slots:
    void init();
    void decode();

signals:
    void startDecode();
    void endFinish();

private:
    const int MAX_PCM_BUFFER_SIZE=192000;

private:
    double time_base;
    AVPacket* packet;
    AVFrame* frame;
    SwrContext* swrCtx;
    QThread* thread;

private:
    void freeResource();
};

class VideoDecoder : public QObject
{
    Q_OBJECT

public:
    VideoDecoder();

signals:
    void startDecode();
    void endFinish();

public slots:
    void init();
    void decode();

private:
    AVPacket* packet;
    double time_base;
    QThread* thread;

private:
    void freeResource();
};

class AudioPlayer : public QObject
{
    Q_OBJECT

public:
    AudioPlayer();
    void setVolumeSlider(QSlider*);

public slots:
    void init();
    void play();

signals:
    void startPlay();
    void proSliderTimerStart();
    void proSliderTimerStop();
    void endFinish();
    void eof();

signals:
    void release(QAudioOutput*);

private:
    void waitProSliderTimerStop();

private:
    QSlider* volume;
    QAudioOutput* audioOut;
    QIODevice* audioDevice;
    AudioReleaser* audioReleaser;
    QThread* thread;

private:
    void freeResource();
};

class VideoPlayer : public QObject
{
    Q_OBJECT

public:
    VideoPlayer();

public slots:
    void init();
    void play();
    void sync();

signals:
    void startPlay();
    void timerStart(int);
    void timerStop();
    void endFinish();

private:
    int videoW, videoH;
    QThread* thread;

private:
    QMutex mut;
    VideoTimer* videoTimer;

private:
    void freeResource();
};


void MultimediaConnect(MultimediaEntry*,AudioDecoder*,VideoDecoder*,AudioPlayer*,VideoPlayer*,VideoDecoderPlayer*);

#endif // MULTIMEDIAMAIN_H
