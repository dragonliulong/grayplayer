#ifndef SLIDER_H
#define SLIDER_H

#include <QPainter>
#include <QString>
#include <QSlider>
#include <QDebug>
#include <QMouseEvent>
#include <QVariantAnimation>
#include <QPropertyAnimation>
#include <QVariant>
#include <QTimer>
#include <cmath>
#include <QStyleOption>
#include <QStyle>
#include <QVBoxLayout>
#include "MultimediaAHelper.h"
#include "MultimediaTime.h"

typedef double DOU;

struct Color
{
    int r,g,b;

    QString ToString()
    { return QString("background:rgb(%1,%2,%3);").arg(r).arg(g).arg(b); }
};

struct Style
{
    int width,height;
    int left,right,top,bottom;
    int radius;
    Color color;

    Style() {}

    Style(int h,int l,int r)
    {
        height=h;
        left=l;
        right=r;
    }

    Style(int w,int rad,int l,int r,int t,int b,Color c)
    {
        width=w;
        radius=rad;
        left=l;
        right=r;
        top=t;
        bottom=b;
        color=c;
    }
};

struct SliderStyle
{
    Style groove;
    Style handle;
    Color add_page;
    Color sub_page;

    void SetGroove(int h,int l,int r)
    { groove=Style(h,l,r); }

    void SetHandle(int w,int rad,int l,int r,int t,int b,Color c)
    { handle=Style(w,rad,l,r,t,b,c); }

    void SetAddPage(Color c)
    { add_page=c; }

    void SetSubPage(Color c)
    { sub_page=c; }

    QString ToString()
    {
        QString s;

        s+="QSlider::groove:";
        s+=QString("horizontal{height:%1px; left:%2px; right:%3px; background:rgb(0,0,0);}").arg(groove.height).arg(groove.left).arg(groove.right);

        s+="QSlider::handle:";
        s+=QString("horizontal{width:%1px; border-radius:%2px; left:%3px; right:%4px; top:%5px; bottom:%6px; %7}")
                .arg(handle.width)
                .arg(handle.radius)
                .arg(handle.left)
                .arg(handle.right)
                .arg(handle.top)
                .arg(handle.bottom)
                .arg(handle.color.ToString());

        s+=QString("QSlider::add-page:horizontal{%1}").arg(add_page.ToString());
        s+=QString("QSlider::sub-page:horizontal{%1}").arg(sub_page.ToString());

        return s;
    }
};

Q_DECLARE_METATYPE(SliderStyle)

class Slider : public QSlider
{
    Q_OBJECT
    Q_PROPERTY(SliderStyle sliderStyle READ GetStyle WRITE SetStyle)

public:
    Slider(QWidget* parent=NULL) : QSlider(Qt::Horizontal, parent)
    {
        qRegisterAnimationInterpolator<SliderStyle>(StyleInterpolator);
        animation=new QPropertyAnimation(this,"sliderStyle");
        connect(this,&Slider::sliderPressed,this,&Slider::setSliderPress);
        connect(this,&Slider::sliderReleased,this,&Slider::setSliderRelease);
        connect(&timer,&QTimer::timeout,this,&Slider::timeoutEvent);
    }

    void init()
    {
        setMinimum(0);
        setMaximum(1<<20);
        setCursor(Qt::PointingHandCursor);

        sliderStyle.SetGroove(2,0,0);  //高 左 右
        sliderStyle.SetHandle(10,5,-5,-5,-4,-4,handleColor);  //宽 半径 左 右 上 下 rgb
        sliderStyle.SetAddPage(addPageColor);
        sliderStyle.SetSubPage(subPageColor);
        this->setStyleSheet(sliderStyle.ToString());

        initStyle=sliderStyle;
        obvious=false;
        sliderPress=false;
    }

    static Color handleColor;
    static Color addPageColor;
    static Color subPageColor;

protected:
    void enterEvent (QEvent*)
    {
        SliderStyle tar;

        if(!obvious)
        {
            tar.SetGroove(6,0,0);  //高 左 右
            tar.SetHandle(20,10,-10,-10,-7,-7,handleColor);  //宽 半径 左 右 上 下 rgb
            tar.SetAddPage(addPageColor);
            tar.SetSubPage(subPageColor);

            play(tar,70);
            obvious=true;
        }
    }

    void leaveEvent(QEvent*)
    {
        if(obvious && !sliderPress)
        {
            play(initStyle,70);
            obvious=false;
        }
    }

    void mousePressEvent(QMouseEvent* e)
    {
        if(e->button()==Qt::LeftButton)
        {
            DOU per = (DOU)e->pos().x()/(DOU)this->width();
            emit skip(per,false);
        }

        QSlider::mousePressEvent(e);
    }

public slots:
    void setSliderPress()
    {
        sliderPress=true;
        lastVal=value();
        timer.start(100);
    }

    void setSliderRelease()
    {
        sliderPress=false;

        if(!curosrIn(this->mapFromGlobal(QCursor::pos())) && obvious)
        {
            play(initStyle,70);
            obvious=false;
        }

        DOU per=(DOU)value()/(DOU)maximum();
        emit skip(per,false);
        timer.stop();
    }

    void timeoutEvent()
    {
        if(value()==lastVal) return;
        DOU per=(DOU)value()/(DOU)maximum();
        emit skip(per,true);
        lastVal=value();
    }

signals:
    void skip(double per,bool can_give_up);

private:
    SliderStyle sliderStyle,initStyle;
    QPropertyAnimation* animation;
    bool obvious,sliderPress;
    QTimer timer;
    int lastVal;

private:
    void play(SliderStyle& tar, int duration)
    {
        animation->stop();

        QVariant CurrentVar,TarVar;
        CurrentVar.setValue(sliderStyle);
        TarVar.setValue(tar);

        animation->setStartValue(CurrentVar);
        animation->setEndValue(TarVar);
        animation->setDuration(duration);
        animation->start();
    }

    bool curosrIn(QPoint pos)
    {
        if(pos.x() >= 0 && pos.x() <= width() &&
           pos.y() >= 0 && pos.y() <= height() ) return true;

        return false;
    }

    SliderStyle GetStyle()
    { return sliderStyle; }

    void SetStyle(SliderStyle& sty)
    {
        this->sliderStyle=sty;
        this->setStyleSheet(sty.ToString());
    }

    static QVariant StyleInterpolator(const SliderStyle& f,const SliderStyle& t,qreal progress);
};

#endif // SLIDER_H
