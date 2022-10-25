#ifndef VOLUMEBUTTON_H
#define VOLUMEBUTTON_H

#include <QDebug>
#include <QPushButton>
#include <QSlider>
#include <QPropertyAnimation>

class Volume : public QSlider
{
    Q_OBJECT

public:
    Volume(QWidget* parent=NULL) : QSlider(Qt::Horizontal, parent) {}

    void init()
    {
        setMinimumSize(105,14);
        setMaximumSize(105,14);

        setMinimum(0);
        setMaximum(1<<10);
        setCursor(Qt::PointingHandCursor);

        QString sty= QString( "QSlider:horizontal{ background:transparent; }"
                              "QSlider::groove:horizontal{ height:4px; border-radius:2px; left:7px; right:7px; background:rgb(100,100,100); }"
                              "QSlider::handle:horizontal{ width:14px; height:14px; border-radius:7px; left:-7px; right:-7px; top:-5px; bottom:-5px; background:rgb(60,60,180); }"
                              "QSlider::add-page:horizontal{ border-radius:2px; background:rgb(60,60,60); }"
                              "QSlider::sub-page:horizontal{ border-radius:2px; background:rgb(60,60,180); }");

        setStyleSheet(sty);
    }
};

#endif // VOLUMEBUTTON_H
