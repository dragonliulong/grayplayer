#ifndef TIMELABEL_H
#define TIMELABEL_H

#include <QLabel>

class TimeLabel : public QLabel
{
    Q_OBJECT

public:
    TimeLabel(QWidget* p=0) : QLabel(p)
    {
        setFont(QFont("微软雅黑",8));
        setStyleSheet("color:rgb(240,240,240);");
        resize(130,36);
    }

    void reset()
    {
        totalTime = 0;
        totalTimeString.clear();
        setText("");
    }

    void setProgressMaxValue(int x)
    {
        progressMaxValue = x;
    }

public slots:
    void progressValueChange(int val)
    {
        double per = (double)val/(double)progressMaxValue;
        double at = per * totalTime;

        int h = at/3600;
        int m = at/60 - h*60;
        int s = at - h*3600 - m*60;

        QString atString = QString("%1:%2:%3").arg(h,2,10,QChar('0')).arg(m,2,10,QChar('0')).arg(s,2,10,QChar('0'));
        setText(atString + " / " + totalTimeString);
    }

    void totalTimeChange(double t)
    {
        if(t > 0)
        {
            totalTime = t;

            int h = t/3600;
            int m = t/60 - h*60;
            int s = t - h*3600 - m*60;

            totalTimeString = QString("%1:%2:%3").arg(h,2,10,QChar('0')).arg(m,2,10,QChar('0')).arg(s,2,10,QChar('0'));
        }
        else
        {
            totalTimeString = "inf";
        }

        setText("00:00:00 / " + totalTimeString);
    }

private:
    QString totalTimeString;
    double totalTime;
    int progressMaxValue;
};

#endif // TIMELABEL_H
