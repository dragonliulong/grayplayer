#ifndef LINEEDIT_H
#define LINEEDIT_H

#include "FramelessWidget.h"
#include "Button.h"
#include <QLineEdit>

class LineEdit : public FramelessWidget
{
    Q_OBJECT

public:
    LineEdit(QWidget* p=0) : FramelessWidget(p)
    {
        setTitleH(60);
        setAttribute(Qt::WA_ShowModal);
        setStyleSheet(styleSheet()+"background:rgb(30,30,40);");
        resize(600,260);

        exit = new Button(this);
        exit->init(EXIT_BUTTON);
        exit->resize(45,40);
        exit->move(width() - exit->width() - 12, 12);
        connect(exit,&Button::clicked,this,&LineEdit::hide);

        accept = new Button(this);
        CustomInfo info;
        info.dy = false;
        info.text0 = "确认";
        accept->initCustom(&info);
        accept->setFont(QFont("微软雅黑",10));
        accept->resize(60,40);
        accept->move(width() - accept->width() - 12, height() - accept->height() - 12);
        connect(accept,&Button::clicked,this,&LineEdit::acceptUrl);

        edit = new QLineEdit(this);
        edit->setStyleSheet("color:black; background:rgb(240,240,240)");
        edit->setFont(QFont("微软雅黑",10));
        edit->resize(width() - 24, 35);
        edit->move(12, 70);

        connect(edit,&QLineEdit::textChanged,this,&LineEdit::textChange);
        connect(edit,&QLineEdit::returnPressed,this,&LineEdit::acceptUrl);
    }

private:
    Button* exit, * accept;
    QLineEdit* edit;

private:
    bool checkText(const QString& text)
    {
        QString url = text.simplified();
        QString tmp;
        int c = 0;

        for(int i=0; i < url.size() && c < 2; i++)
        {
            tmp += url[i];
            if(url[i] == '/') c++;
        }

        if(tmp == "http://" || tmp == "https://" || tmp == "rtmp://" || tmp == "rtsp://")
            return true;

        return false;
    }

signals:
    void acceptUrlNow(QString url);

public slots:
    void textChange(const QString& text)
    {
        if(checkText(text))
            edit->setStyleSheet("color:black; background:rgb(240,240,240)");
        else
            edit->setStyleSheet("color:red; background:rgb(240,240,240)");
    }

    void acceptUrl()
    {
        if(checkText(edit->text()))
        {
            QString url = edit->text().simplified();
            emit acceptUrlNow(url);
            hide();
        }
    }

protected:
    void paintEvent(QPaintEvent*)
    {
        int x=15, y=43;

        QPainter p(this);
        p.setFont(QFont("微软雅黑",11,100));
        p.setPen(QColor(240,240,240));
        p.drawText(x,y,"添加流");

        y = 140;
        int h = 25;

        p.setFont(QFont("微软雅黑",10));
        p.drawText(x,y,"规则:"); y+=h;
        p.drawText(x,y,"1. 必须以 [ http:// 或 https:// 或 rtmp:// 或 rtsp:// ] 开头"); y+=h;
        p.drawText(x,y,"2. 允许前导和后导空格"); y+=h;
    }
};

#endif // LINEEDIT_H
