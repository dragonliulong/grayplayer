#include "GrayPlayer.h"
#include "ui_GrayPlayer.h"
#include <QDebug>
#include <QFileDialog>
#include <QApplication>
#include <QTimer>
#include <QSettings>
#include <QLibrary>
#include "MultimediaType.h"
#include "MultimediaExit.h"
#include "MultimediaAddSetting.h"

GrayPlayer::GrayPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui:: MainWindow)
{
    ui->setupUi(this);

    initVideoArea();
    initExPlayList();
    initPlayList();
    initMainWindow();
    initProgress();
    initVolume();
    initMultimedia();
    initButtons();
    initTimeLabel();
    initSettingWidget();
}

GrayPlayer::~GrayPlayer()
{
    set_exit_flag(false);
    emit stopPlayNow(0);

    int count = 1000;

    while(!get_exit_flag() && count > 0)
    {
        QThread::msleep(1);
        count--;
    }

    delete ui;
}

void GrayPlayer::expansionPlayList(int pre_state)
{
    if(pre_state == 0)
    {
        ui->centralLayout->addWidget(playList);
        ui->centralLayout->setStretch(0,5);
        ui->centralLayout->setStretch(1,1);
        playList->show();
    }
    else
    {
        ui->centralLayout->removeWidget(playList);
        playList->hide();
    }
}

void GrayPlayer::hidePlayList()
{
    exPlayList->setText("+");
    ui->centralLayout->removeWidget(playList);
    playList->hide();
}

void GrayPlayer::showMaxOrNormal()
{
    if(!isMaximized()) showMaximized();
    else showNormal();
}

void GrayPlayer::showMin()
{
    showMinimized();
}

void GrayPlayer::exit()
{
    QApplication::exit();
}

void GrayPlayer::openFile()
{
    fileName = QFileDialog::getOpenFileName(this, tr("打开本地文件"), tr(""), tr(showTypes.c_str())).toUtf8();

    if(fileName.size() > 0)
    {
        set_multimedia_type(fileName.data(), NULL);
        playPrepare();
        emit open(fileName.data());
    }
}

void GrayPlayer::playPrepare(int flag)
{
    if(get_multimedia_type() != NETWORK_TYPE)
    {
        //进度条显示
        progress->setValue(progress->minimum());
        progress->show();

        //videoArea下面空出10像素留给进度条显示上半部分
        ui->VideoAreaLayout->setContentsMargins(0,0,0,10);
    }
    else
    {
        progress->hide();
        ui->VideoAreaLayout->setContentsMargins(0,0,0,0);
    }

    //隐藏beginWidget
    ui->videoArea->getBeginWidget()->hideFailHint();
    ui->videoArea->getBeginWidget()->hide();
    ui->videoArea->update();

    //timeLabel重置并显示
    timeLabel->reset();
    timeLabel->show();

    //设置play按钮状态
    ui->play->setText("PA");

    if(flag == 1) emit playPrepareFinish(1);
}

void GrayPlayer::playStop(int flag)
{
    if(flag == 0 || flag == -1)
    {
        //进度条隐藏
        progress->setValue(progress->minimum());
        progress->hide();

        //videoArea还原
        ui->VideoAreaLayout->setContentsMargins(0,0,0,0);

        //显示beginWidget
        ui->videoArea->getBeginWidget()->show();
        ui->videoArea->update();

        //timeLabel重置并隐藏
        timeLabel->reset();
        timeLabel->hide();

        //设置play按钮状态
        ui->play->setText("PA");

        if(flag == -1)
        {
            ui->videoArea->getBeginWidget()->showFailHint(3000);
        }
    }
}

void GrayPlayer::playEof()
{
    EOF_DEAL deal = getEofDeal();

    switch(deal)
    {
    case EOF_STOP:
        emit stopPlayNow(0);
        break;

    case EOF_PAUSE:
        emit ui->play->clicked();
        break;

    case EOF_REPEAT:
        emit repeatPlayNow();
        break;

    case EOF_NEXT:
        emit ui->next->clicked();
        break;
    }
}

//----------------------------------------------adjust-----------------------------------------------

void GrayPlayer::adjustVolume()
{
    int x = ui->volumeButton->x() + ui->volumeButton->width();
    int y = ui->volumeButton->y() + (ui->volumeButton->height() - volume->height()) / 2;

    volume->move(x, y);
}

void GrayPlayer::adjustProgress()
{
    progress->move(0, ui->videoArea->y() + ui->videoArea->height());
    progress->resize(ui->videoArea->width(), 20);
}

void GrayPlayer::adjustTimeLabel()
{
    timeLabel->move(21, timeLabel->parentWidget()->height() - timeLabel->height() - 21);
}

void GrayPlayer::adjustExPlayList()
{
    exPlayList->move(ui->videoArea->width() - exPlayList->width() - 18, exPlayList->parentWidget()->height() - exPlayList->height() - 25);
}

void GrayPlayer::adjustAll()
{
    adjustVolume();
    adjustProgress();
    adjustTimeLabel();
    adjustExPlayList();
}
