#include "MultimediaAReleaser.h"


AudioReleaser::AudioReleaser()
{
    thread =  new QThread();
    moveToThread(thread);
    thread->start();
}

void AudioReleaser::releaseAudioOutput(QAudioOutput* audioOutput)
{
    audioOutput->stop();
    delete audioOutput;
}
