#ifndef MULTIMEDIAVDT_H
#define MULTIMEDIAVDT_H

/* 弃用

#include <QThread>
#include <QMutex>
#include <MultimediaResource.h>
#include <MultimediaHW.h>

class VideoDecodeTask : public QThread
{
    Q_OBJECT

public:
    VideoDecodeTask(int,int,double);

public:
    bool isTasking();
    bool isFrameTargetNULL();
    void setFrameTargetNULL();
    void freeFrameTarget();
    AVFrame* getFrame();
    YUV getYUV();

public slots:
    void task();

private:
    void setTasking(bool);

private:
    AVFrame* frame;
    AVFrame* frameTarget;
    QMutex mut;

private:
    int videoW,videoH;
    double time_base;
    double time_at;
    bool tasking;
};

*/

#endif // MULTIMEDIAVDT_H
