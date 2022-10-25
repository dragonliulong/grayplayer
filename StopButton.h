#ifndef STOPBUTTON_H
#define STOPBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QHelpEvent>
#include <QToolTip>

class StopButton : public QPushButton
{
    Q_OBJECT

public:
    StopButton(QWidget* p=0) : QPushButton(p)
    {
        connect(this,&StopButton::clicked,this,&StopButton::stopSlot);
    }

signals:
    void stopNow(int);

public slots:
    void stopSlot()
    {
        emit stopNow(0);
    }

protected:
    void paintEvent(QPaintEvent*)
    {
        QPainter painter(this);

        double w=15, h=15;
        double x=(double)(width()-w)/2.0 , y=(double)(height()-h)/2.0;
        QRectF rectF(x,y,w,h);

        painter.setPen(Qt::transparent);
        painter.setBrush(QColor(60,60,150));
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawRoundedRect(rectF,4,4);
    }

    bool event(QEvent* e)
    {
        if(e->type() == QEvent::ToolTip)
        {
            QHelpEvent* helpE = static_cast<QHelpEvent*>(e);
            QToolTip::showText(helpE->globalPos(), "停止", NULL, QRect(), 3000);
        }

        return QPushButton::event(e);
    }
};

#endif // STOPBUTTON_H
