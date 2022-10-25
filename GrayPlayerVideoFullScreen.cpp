#include "GrayPlayer.h"
#include "ui_GrayPlayer.h"

static Qt::WindowFlags videoAreaType;

void GrayPlayer::videoShowFullScreen()
{
    //emit fullscreenNow();

    //判断当前是不是视频类型

    if(!ui->videoArea->isFullScreen()) videoShowFullScreenPri();
    else videoShowNormalPri();
}

void GrayPlayer::videoShowFullScreenPri()
{
    videoAreaType = ui->videoArea->windowFlags();
    ui->videoArea->setWindowFlag(Qt::Window);
    ui->videoArea->showFullScreen();
}

void GrayPlayer::videoShowNormalPri()
{
    ui->videoArea->setWindowFlags(videoAreaType);
    ui->videoArea->showNormal();
}
