#ifndef MULTIMEDIAVDP_H
#define MULTIMEDIAVDP_H

#include <QObject>
#include <QThread>
#include <QWaitCondition>
#include "MultimediaTime.h"
#include "MultimediaResource.h"

class VideoDecoderPlayer : public QObject
{
    Q_OBJECT

public:
    VideoDecoderPlayer();

signals:
    void startDecodePlay();
    void timerStart(int);
    void timerStop();
    void endFinish();

public slots:
    void init();
    void decodePlay();
    bool receiveFrame();
    bool isAVSync();

private:
    AVPacket* packet;
    AVFrame* frame;
    double time_base;
    double time_at;
    QThread* thread;

private:
    QMutex mut;
    VideoTimer* videoTimer;

private:
    bool skip;
    double skip_at;
    int skip_wait_limit;
    uint64_t skip_start_clock;

private:
    void d3d9Deal();
    void d3d11Deal();

private:
    void freeResource();
};

#endif // MULTIMEDIAVDP_H
