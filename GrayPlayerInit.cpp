#include "GrayPlayer.h"
#include "ui_GrayPlayer.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <windows.h>
#include <dwmapi.h>
#include <windowsx.h>
#include "MultimediaType.h"
#include "MultimediaDecodeSetting.h"
#include "MultimediaInterrupt.h"

void GrayPlayer::initMainWindow()
{
    setWindowFlag(Qt::FramelessWindowHint);

    //---------------------------------DWM窗口效果--------------------------------------------

    DWORD style = GetWindowLongPtr((HWND)winId(), GWL_STYLE);
    SetWindowLongPtr((HWND)winId(), GWL_STYLE, style | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);

    BOOL isDwmComEnabled = false;
    DwmIsCompositionEnabled(&isDwmComEnabled);

    if (isDwmComEnabled)
    {
        MARGINS margins =
        {
            .cxLeftWidth = 0,
            .cxRightWidth = 0,
            .cyTopHeight = 1,
            .cyBottomHeight = 1
        };

        DwmExtendFrameIntoClientArea((HWND)winId(), &margins);
    }

    //-----------------------------------鼠标监控-----------------------------------------

    this->setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    ui->title->setMouseTracking(true);
    ui->videoArea->setMouseTracking(true);

    //-----------------------------------初始化成员----------------------------------------

    leftButtonPress = false;
    stretching = false;

    //------------------------------------------------------------------------------------

    connect(this,SIGNAL(resizeNow()),this,SLOT(adjustAll()));

    setMinimumSize(920,680);
    resize(minimumSize());
}

void GrayPlayer::initVideoArea()
{
    connect(ui->videoArea,&VideoArea::resizeNow,this,&GrayPlayer::adjustAll);
}

void GrayPlayer::initButtons()
{
    ui->play->init(PLAY_BUTTON);
    ui->before->init(BEFORE_BUTTON);
    ui->next->init(NEXT_BUTTON);
    ui->exit->init(EXIT_BUTTON);
    ui->max->init(MAX_BUTTON);
    ui->min->init(MIN_BUTTON);
    ui->setting->init(SETTING_BUTTON);

    connect(ui->max,&Button::clicked,this,&GrayPlayer::showMaxOrNormal);
    connect(ui->min,&Button::clicked,this,&GrayPlayer::showMin);
    connect(ui->exit,&Button::clicked,this,&GrayPlayer::exit);
    connect(ui->videoArea->getBeginWidget()->getOpenButton(),&Button::clicked,this,&GrayPlayer::openFile);
}

void GrayPlayer::initProgress()
{
    progress=new Slider(ui->centralWidget);
    progress->init();
    progress->hide();
}

void GrayPlayer::initVolume()
{
    volume=new Volume(ui->centralWidget);
    volume->init();
    volume->setValue(volume->maximum() * 0.7);
}

void GrayPlayer::initMultimedia()
{
    //读取解码设置
    readDecodeSetting();

    multimediaEntry=new MultimediaEntry();
    audioDecoder=new AudioDecoder();
    videoDecoder=new VideoDecoder();
    audioPlayer=new AudioPlayer();
    videoPlayer=new VideoPlayer();
    videoDecoderPlayer=new VideoDecoderPlayer();

    initProSliderTimer(progress);
    audioPlayer->setVolumeSlider(volume);

    multimediaEntry->setVideoShowAt(ui->videoArea);

    MultimediaConnect(multimediaEntry,audioDecoder,videoDecoder,audioPlayer,videoPlayer,videoDecoderPlayer);

    connect(audioPlayer,&AudioPlayer::eof,this,&GrayPlayer::playEof);
    connect(progress,&Slider::sliderPressed,multimediaEntry,&MultimediaEntry::sliderPress);
    connect(progress,&Slider::sliderReleased,multimediaEntry,&MultimediaEntry::sliderRelease);
    connect(progress,&Slider::skip,multimediaEntry,&MultimediaEntry::skip);
    connect(this,&GrayPlayer::open,multimediaEntry,&MultimediaEntry::open);
    connect(ui->stop,&StopButton::stopNow,multimediaEntry,&MultimediaEntry::stop);  //stop
    connect(ui->stop,&StopButton::stopNow,multimediaEntry->getInterrupter(),&Interrupter::setInterruptFlagTrue);  //stop
    connect(multimediaEntry,&MultimediaEntry::stopFinishNow,this,&GrayPlayer::playStop);
    connect(ui->play,&Button::clicked,multimediaEntry,&MultimediaEntry::pause);
    connect(multimediaEntry,&MultimediaEntry::openFail,this,&GrayPlayer::playStop);
    connect(this,&GrayPlayer::stopPlayNow,multimediaEntry,&MultimediaEntry::stop);  //stop
    connect(this,&GrayPlayer::stopPlayNow,multimediaEntry->getInterrupter(),&Interrupter::setInterruptFlagTrue);  //stop

    connect(playList,&PlayList::requestStopPlay,multimediaEntry,&MultimediaEntry::stop);  //stop
    connect(playList,&PlayList::requestStopPlay,multimediaEntry->getInterrupter(),&Interrupter::setInterruptFlagTrue);  //stop
    connect(multimediaEntry,&MultimediaEntry::stopFinishNow,playList,&PlayList::playStopFinish);
    connect(playList,&PlayList::requestPlayPrepare,this,&GrayPlayer::playPrepare);
    connect(this,&GrayPlayer::playPrepareFinish,playList,&PlayList::playPrepareFinish);
    connect(playList,&PlayList::open,multimediaEntry,&MultimediaEntry::open);
    connect(this,&GrayPlayer::repeatPlayNow,playList,&PlayList::playRepeat);
    connect(playList,&PlayList::error,this,&GrayPlayer::playStop);
    connect(ui->before,&Button::clicked,playList,&PlayList::playBefore);
    connect(ui->next,&Button::clicked,playList,&PlayList::playNext);

    //-----------------------------------------------------------------------

    QString typeString;

    for(int i=0; i < (int)audioTypes.size(); i++)
    {
        if(i!=0) typeString += " ";
        typeString += "*.";
        typeString += QString::fromStdString(audioTypes[i]);
    }

    for(int i=0; i < (int)videoTypes.size(); i++)
    {
        typeString += " ";
        typeString += "*.";
        typeString += QString::fromStdString(videoTypes[i]);
    }

    showTypes = QString("视频和音频类型(%1)").arg(typeString).toStdString();

    //------------------------------------------------------------------------
}

void GrayPlayer::initTimeLabel()
{
    timeLabel = new TimeLabel(ui->centralWidget);
    timeLabel->setProgressMaxValue(progress->maximum());
    timeLabel->hide();

    connect(progress, &QSlider::valueChanged,timeLabel,&TimeLabel::progressValueChange);
    connect(multimediaEntry,&MultimediaEntry::totalTimeChange,timeLabel,&TimeLabel::totalTimeChange);
}

void GrayPlayer::initPlayList()
{
    //初始typeMap
    initTypeMap();

    playList = new PlayList(ui->centralWidget);

    CustomInfo leftAddInfo;
    leftAddInfo.text0 = "+";
    leftAddInfo.tip0 = "添加本地文件";
    leftAddInfo.dy = false;

    CustomInfo rightAddInfo;
    rightAddInfo.text0 = "+";
    rightAddInfo.tip0 = "添加流";
    rightAddInfo.dy = false;

    playList->setLeftAddInfo(&leftAddInfo);
    playList->setRightAddInfo(&rightAddInfo);

    playList->getLeftOpt()->setText("本地");
    playList->getRightOpt()->setText("网络");

    playList->getTitle()->setText("播放列表");

    connect(playList->getBackButton(),&Button::clicked,this,&GrayPlayer::hidePlayList);
    connect(this,&GrayPlayer::open,playList,&PlayList::addFile);

    playList->hide();
}

void GrayPlayer::initExPlayList()
{
    exPlayList = new Button(ui->centralWidget);

    CustomInfo info;
    info.dy = true;
    info.text0 = "+";
    info.text1 = "-";
    info.tip0 = "显示播放列表";
    info.tip1 = "隐藏播放列表";
    exPlayList->setFont(QFont("微软雅黑",18,24));

    exPlayList->initCustom(&info);
    exPlayList->setMinimumSize(30,30);
    exPlayList->setMaximumSize(30,30);

    connect(exPlayList,&Button::stateChangeCustomSignal,this,&GrayPlayer::expansionPlayList);
}

void GrayPlayer::initSettingWidget()
{
    settingWidget=new SettingWidget();
    settingWidget->follow(this);
    settingWidget->hide();
    connect(ui->setting,&Button::clicked,settingWidget,&SettingWidget::showFollow);

    if(renderMode == D3D11)
    {
        connect(videoD3D11, &VideoD3D11::showFilterNow, settingWidget->getD3D11VAFilterWidget(), &D3D11VAFilterWidget::showFilterNow);
        connect(videoD3D11, &VideoD3D11::hideFilterNow, settingWidget->getD3D11VAFilterWidget(), &D3D11VAFilterWidget::hideFilterNow);
    }

    if(renderMode == D3D9)
    {
        connect(videoD3D9, &VideoD3D9::showFilterNow, settingWidget->getDXVAHDFilterWidget(), &DXVAHDFilterWidget::showFilterNow);
        connect(videoD3D9, &VideoD3D9::hideFilterNow, settingWidget->getDXVAHDFilterWidget(), &DXVAHDFilterWidget::hideFilterNow);
    }
}
