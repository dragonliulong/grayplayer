#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>

class AboutWidget : public QWidget
{
    Q_OBJECT

public:
    AboutWidget(QWidget* p=0) : QWidget(p) {}

protected:
    void paintEvent(QPaintEvent*)
    {
        QPainter painter(this);

        painter.setPen(Qt::transparent);
        QRect rect(15,20,400,80);
        painter.drawImage(rect,QImage(":/aboutLogo.jpg").scaled(QSize(400,80),Qt::KeepAspectRatio,Qt::SmoothTransformation));

        painter.setPen(Qt::black);
        painter.setFont(QFont("微软雅黑",9));
        painter.drawText(15,130,"GrayPlayer（灰度播放器）");
        painter.drawText(15,160,"界面库: Qt 5.15");
        painter.drawText(15,190,"解码库: ffmpeg（软解, DXVA2硬解, D3D11VA硬解）");
        painter.drawText(15,220,"渲染API: Direct3D9, Direct3D11");
        painter.drawText(15,250,"推荐最低操作系统: win7");
        painter.drawText(15,280,"当前版本: 1.3");
    }
};

#endif // ABOUTWIDGET_H
