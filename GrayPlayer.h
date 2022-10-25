#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QMouseEvent>
#include <QDebug>
#include <QByteArray>
#include "MultimediaResource.h"
#include "MultimediaMain.h"
#include "Volume.h"
#include "Slider.h"
#include "Logo.h"
#include "SettingWidget.h"
#include "TimeLabel.h"
#include "PlayList.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GrayPlayer : public QMainWindow
{
    Q_OBJECT

public:
    GrayPlayer(QWidget *parent = nullptr);
    ~GrayPlayer();

public:
    static void resetDecodeSetting();

private:  //所有ui控件
    Ui::MainWindow* ui;
    Volume* volume;
    Slider* progress;
    TimeLabel* timeLabel;
    SettingWidget* settingWidget;
    PlayList* playList;
    Button* exPlayList;

private:  //鼠标左键按下相关
    bool leftButtonPress;
    QPoint pressMouseAt, pressThisAt;

private:  //窗口拉伸相关
    bool stretching;
    QPoint basePoint;
    bool changeW, changeH;
    bool changeX, changeY;

private:
    MultimediaEntry* multimediaEntry;
    AudioDecoder* audioDecoder;
    VideoDecoder* videoDecoder;
    AudioPlayer* audioPlayer;
    VideoPlayer* videoPlayer;
    VideoDecoderPlayer* videoDecoderPlayer;

private:
    QByteArray fileName;
    string showTypes;

private:
    void initButtons();
    void initProgress();
    void initMainWindow();
    void initVolume();
    void initMultimedia();
    void initTimeLabel();
    void initSettingWidget();
    void initPlayList();
    void initExPlayList();
    void initVideoArea();

private:
    bool isInBorder(Qt::CursorShape&);
    void adjustVolume();
    void adjustProgress();
    void adjustTimeLabel();
    void adjustExPlayList();

private:
    void readDecodeSetting();

signals:
    void open(char* file);
    void playPrepareFinish(int);
    void resizeNow();
    void stopPlayNow(int);
    void repeatPlayNow();

public slots:
    void openFile();
    void playPrepare(int flag=0);
    void playStop(int);
    void playEof();
    void expansionPlayList(int);
    void hidePlayList();
    void adjustAll();
    void showMaxOrNormal();
    void showMin();
    void exit();

protected:
    void mouseDoubleClickEvent (QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    bool nativeEvent(const QByteArray&, void*, long*);
    void resizeEvent(QResizeEvent*);
};
#endif // MAINWINDOW_H
