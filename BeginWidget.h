#ifndef BEGINWIDGET_H
#define BEGINWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QLabel>
#include <Button.h>
#include <Logo.h>

class BeginWidget : public QWidget
{
    Q_OBJECT

public:
    BeginWidget(QWidget* parent) : QWidget(parent)
    {
        setMouseTracking(true);

        //open按钮
        open = new Button(this);
        open->init(OPEN_BUTTON);
        open->setCursor(Qt::PointingHandCursor);
        open->setMinimumSize(140,70);
        open->setMaximumSize(140,70);

        //logo
        logo = new Logo(this);
        logo->setAttribute(Qt::WA_TranslucentBackground);

        //label
        failHint = new QLabel(this);
        failHint->setFont(QFont("微软雅黑",12));
        failHint->setStyleSheet("color:rgb(230,230,230); background:rgba(0,255,255,50);");
        failHint->setText("打开失败/中断");
        failHint->move(0,2);
        failHint->setMaximumSize(200,70);
        failHint->setMinimumSize(200,70);
        failHint->setAlignment(Qt::AlignCenter);
        failHint->hide();

        //timer
        timer.setSingleShot(true);
        connect(&timer,&QTimer::timeout,failHint,&QLabel::hide);
    }

    Button* getOpenButton()
    {
        return open;
    }

    void showFailHint(int t)
    {
        failHint->show();
        timer.start(t);
    }

    void hideFailHint()
    {
        failHint->hide();
        timer.stop();
    }

private:
    Button* open;
    Logo* logo;
    QLabel* failHint;
    QTimer timer;

protected:
    void paintEvent(QPaintEvent*)
    {
        QLinearGradient outlineGradient(0,0,this->width(),0);
        outlineGradient.setColorAt(0,   QColor(20, 20, 120));
        outlineGradient.setColorAt(0.1, QColor(20, 20, 180));
        outlineGradient.setColorAt(0.3, QColor(20, 20, 220));
        outlineGradient.setColorAt(0.5, QColor(20, 20, 250));
        outlineGradient.setColorAt(0.7, QColor(20, 20, 220));
        outlineGradient.setColorAt(0.9, QColor(20, 20, 180));
        outlineGradient.setColorAt(1,   QColor(20, 20, 120));

        QImage img(":/showWindow.jpg");
        QPixmap pix=QPixmap::fromImage(img);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QColor(0,0,0,0));
        painter.setBrush(outlineGradient);
        painter.drawRect(0,0,this->width(),2);
        painter.drawPixmap(0,2,pix.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    }

    void resizeEvent(QResizeEvent*)
    {
        int inter = 15;
        int wholeH = logo->height() + open->height() + inter;

        int x_logo = (width() - logo->width())/2;
        int y_logo = (height() - wholeH)/2;
        int x_open = (width() - open->width())/2;
        int y_open = y_logo + logo->height() + inter;

        logo->move(x_logo,y_logo);
        open->move(x_open,y_open);
    }
};

#endif // BEGINWIDGET_H
