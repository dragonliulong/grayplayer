#ifndef LOGO_H
#define LOGO_H

#include <QLabel>
#include <QPainter>

class Logo : public QLabel
{
    Q_OBJECT

public:
    Logo(QWidget* parent=0) : QLabel(parent)
    {
        QSize is(450,90);
        setMaximumSize(is);
        setMinimumSize(is);
    }

protected:
    void paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.drawImage(0,0,QImage(":/logo.ico").scaled(size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
};

#endif // LOGO_H
