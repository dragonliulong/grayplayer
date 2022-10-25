#ifndef VIDEOAREA_H
#define VIDEOAREA_H

#include "BeginWidget.h"
#include <QVBoxLayout>
#include <QMouseEvent>

class VideoArea : public QWidget
{
    Q_OBJECT

public:
    VideoArea(QWidget* parent) : QWidget(parent)
    {
        setMouseTracking(true);

        beginWidget = new BeginWidget(this);

        QVBoxLayout* layout = new QVBoxLayout();
        layout->setContentsMargins(0,0,0,0);
        layout->addWidget(beginWidget);
        setLayout(layout);
    }

    BeginWidget* getBeginWidget()
    {
        return beginWidget;
    }

private:
    BeginWidget* beginWidget;

signals:
    void resizeNow();

protected:
    void paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.setPen(Qt::transparent);
        painter.setBrush(Qt::black);
        painter.drawRect(0,0,width(),height());
    }

    void resizeEvent(QResizeEvent*)
    {
        emit resizeNow();
    }
};

#endif // VIDEOAREA_H
