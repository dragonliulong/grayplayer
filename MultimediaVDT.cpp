/* 弃用

#include "MultimediaVDT.h"
#include "MultimediaVSDL.h"

VideoDecodeTask::VideoDecodeTask(int w, int h, double tb) : QThread()
{
    videoW=w;
    videoH=h;
    time_base=tb;

    frame=av_frame_alloc();
    frameTarget=NULL;

    tasking=false;
    time_at=0;

    this->moveToThread(this);
    this->start();
}

bool VideoDecodeTask::isTasking()
{
    mut.lock();
    bool x=tasking;
    mut.unlock();
    return x;
}

void VideoDecodeTask::setTasking(bool x)
{
    mut.lock();
    tasking=x;
    mut.unlock();
}

void VideoDecodeTask::setFrameTargetNULL()
{
    frameTarget=NULL;
}

void VideoDecodeTask::freeFrameTarget()
{
    if(frameTarget)
    {
        av_frame_free(&frameTarget);
        frameTarget=NULL;
    }
}

bool VideoDecodeTask::isFrameTargetNULL()
{
    return frameTarget==NULL ? true:false;
}

YUV VideoDecodeTask::getYUV()
{
    return { frameTarget, time_at, false};
}

AVFrame* VideoDecodeTask::getFrame()
{
    return frame;
}

void VideoDecodeTask::task()
{
    setTasking(true);

    //---------------------------------------------------------------

    time_at = time_base * frame->best_effort_timestamp;
    frameTarget=av_frame_alloc();

    //确定目标帧
    if(hwType != AV_HWDEVICE_TYPE_NONE)
    {
        //av_hwframe_transfer_data(frameTarget, frame, 0);
    }
    else
    {
        frameTarget->format = frame->format;
        frameTarget->width = frame->width;
        frameTarget->height = frame->height;

        av_frame_get_buffer(frameTarget,0);
        av_frame_copy(frameTarget, frame);
    }

    //---------------------------------------------------------------

    setTasking(false);
}

*/


