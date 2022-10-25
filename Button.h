#ifndef BUTTON_H
#define BUTTON_H
#include <QPushButton>
#include <QPropertyAnimation>
#include <QString>
#include <QVariant>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QRect>
#include <QThread>
#include <QEvent>
#include <QVector>
#include <QString>
#include <QVariantAnimation>
#include <QHelpEvent>
#include <QToolTip>

/* 0 播放
 * 1 上一个
 * 2 下一个
 * 3 退出
 * 4 最大化
 * 5 最小化
 * 6 打开文件
 * 7 设置
 * 8 停止
*/

enum ButtonType
{
    PLAY_BUTTON,
    BEFORE_BUTTON,
    NEXT_BUTTON,
    EXIT_BUTTON,
    MAX_BUTTON,
    MIN_BUTTON,
    OPEN_BUTTON,
    SETTING_BUTTON,
    STOP_BUTTON,
    CUSTOM_BUTTON
};

struct ColorA
{
    int r,g,b;
    double a;

    QString ToString()
    { return QString("rgba(%1,%2,%3,%4);").arg(r).arg(g).arg(b).arg(a); }
};

struct ButtonColor
{
    ColorA BackGroundColor;
    ColorA TextColor;
    ColorA BorderColor;

    QString ToString(int radius=0)
    {
        QString s1="background:"+BackGroundColor.ToString();
        QString s2="color:"+TextColor.ToString();
        QString s3="border:1px solid "+BorderColor.ToString();
        QString s4=QString("border-radius:%1px;").arg(radius);
        return s1+s2+s3+s4;
    }
};

struct CustomInfo
{
    QString text0;
    QString text1;
    QString tip0;
    QString tip1;
    bool dy;
};

Q_DECLARE_METATYPE(ButtonColor)

class Button : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(ButtonColor color READ GetColor WRITE SetColor)

public:  
    Button(QWidget* parent=NULL) : QPushButton(parent), kind(0), customInfo(NULL)
    {
        qRegisterAnimationInterpolator<ButtonColor>(ColorInterpolator);
        animation=new QPropertyAnimation(this,"color");
    }

    void init(int kind)
    {
        this->setCursor(Qt::PointingHandCursor);
        this->setFlat(true);
        this->setText(texts[kind]);
        int textSize= (kind>=0 && kind<=2) ? 13:12;
        this->setFont((QFont("Arial",textSize)));

        if(kind==OPEN_BUTTON)
        {
            color={{50,50,255,0.3}, {255,255,255,1}, {255,255,255,0}};
            this->setStyleSheet(color.ToString(35));
        }
        else
        {
            color={{255,255,255,0}, {255,255,255,0.7}, {255,255,255,0}};
            this->setStyleSheet(color.ToString());
        }

        this->kind = kind;
        if(kind == PLAY_BUTTON) connect(this,&Button::clicked,this,&Button::playStateChange);
    }

protected:
    void enterEvent(QEvent*)
    {
        ButtonColor tar;

        if(kind==OPEN_BUTTON) tar={{50,50,255,0.7}, {255,255,255,1}, {255,255,255,0}};
        else if(kind==EXIT_BUTTON) tar={{150,0,0,0.3}, {255,0,0,1}, {255,0,0,1}};
        else tar={{255,255,255,0.15}, {255,255,255,1}, {255,255,255,1}};

        play(tar,200);
    }

    void leaveEvent(QEvent*)
    {
        ButtonColor tar;

        if(kind==OPEN_BUTTON) tar={{50,50,255,0.3}, {255,255,255,1}, {255,255,255,0}};
        else tar={{255,255,255,0}, {255,255,255,0.7}, {255,255,255,0}};

        play(tar,200);
    }

    void hideEvent(QHideEvent*)
    {
        leaveEvent(NULL);
    }

public slots:
    void playStateChange()
    {
        QString s = ( text() == "PL" ) ? "PA" : "PL";
        setText(s);
    }

private:
    int kind;
    ButtonColor color;
    QPropertyAnimation* animation;
    QVector<QString> texts={"PA","BE","NE","E","X","N","OPEN","T","ST","自定义"};
    QVector<QString> toolTips={"暂停","上一个","下一个","关闭","最大化","最小化","打开本地文件","设置","停止","自定义"};

    void play(ButtonColor& tar, int duration)
    {
        animation->stop();

        QVariant CurrentVar,TarVar;
        CurrentVar.setValue(color);
        TarVar.setValue(tar);

        animation->setStartValue(CurrentVar);
        animation->setEndValue(TarVar);
        animation->setDuration(duration);

        animation->start();
    }

    ButtonColor GetColor()
    { return color; }

    void SetColor(ButtonColor& color)
    {
        this->color=color;
        if(kind==OPEN_BUTTON) this->setStyleSheet(color.ToString(35));
        else this->setStyleSheet(color.ToString());
    }

    static ColorA IncColorA(const ColorA& c,int x,int y,int z,double t);
    static QVariant ColorInterpolator(const ButtonColor& f,const ButtonColor& t,qreal progress);

protected:
    bool event(QEvent* e)
    {
        if(e->type() == QEvent::ToolTip)
        {
            QHelpEvent* helpE = static_cast<QHelpEvent*>(e);
            QString t = toolTips[kind];

            if(kind == PLAY_BUTTON) t = (text() == "PA") ? "暂停" : "播放";
            else if(kind == CUSTOM_BUTTON && customInfo && customInfo->dy)
                t = ( text() == customInfo->text0 ) ? customInfo->tip0 : customInfo->tip1;

            QToolTip::showText(helpE->globalPos(), t, NULL, QRect(), 3000);
        }

        return QPushButton::event(e);
    }

//------------------------------------------------自定义-------------------------------------------------

public:
    void initCustom(CustomInfo* info)
    {
        kind = CUSTOM_BUTTON;
        customInfo = new CustomInfo();
        customInfo->text0 = info->text0;
        customInfo->text1 = info->text1;
        customInfo->tip0 = info->tip0;
        customInfo->tip1 = info->tip1;
        customInfo->dy = info->dy;

        texts[kind] = customInfo->text0;
        toolTips[kind] = customInfo->tip0;

        this->setCursor(Qt::PointingHandCursor);
        this->setFlat(true);
        this->setText(texts[kind]);

        color={{255,255,255,0}, {255,255,255,0.7}, {255,255,255,0}};
        this->setStyleSheet(color.ToString());

        if(customInfo->dy) connect(this,&Button::clicked,this,&Button::stateChangeCustom);
    }

private:
    CustomInfo* customInfo;

signals:
    void stateChangeCustomSignal(int pre_state);

public slots:
    void stateChangeCustom()
    {
        if(!customInfo || !customInfo->dy) return;
        int pre_state = ( text() == customInfo->text0 ) ? 0 : 1;
        QString s = ( text() == customInfo->text0 ) ? customInfo->text1 : customInfo->text0;
        setText(s);

        emit stateChangeCustomSignal(pre_state);
    }
};

#endif // BUTTON_H
