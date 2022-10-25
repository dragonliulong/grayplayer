#ifndef TITLE_H
#define TITLE_H

#include <QLabel>
#include <QMouseEvent>
#include <QCursor>
#include <QDebug>

class Title : public QLabel
{
    Q_OBJECT

public:
    Title(QWidget* parent) : QLabel(parent)
    {   
        this->mainWindow=parent;
        this->setMouseTracking(true);
        mousePress=false;
        douClick=0;
    }

    void setMainFrame(QWidget* mainFrame)
    { this->mainFrame=mainFrame; }

protected:
    void mouseMoveEvent(QMouseEvent*)
    {
        if(!mousePress) return;

        int x=QCursor::pos().x()-pressMouseAt.x();
        int y=QCursor::pos().y()-pressMouseAt.y();

        mainFrame->move(pressMainFrameAt.x()+x, pressMainFrameAt.y()+y);
    }

    void mousePressEvent(QMouseEvent* e)
    {
        if(e->button()==Qt::LeftButton)
        {
            pressMouseAt=QCursor::pos();
            pressMainFrameAt=mainFrame->pos();
            mousePress=true;
        }
    }

    void mouseReleaseEvent(QMouseEvent* e)
    {
        if(e->button()==Qt::LeftButton) mousePress=false;
    }

    void mouseDoubleClickEvent (QMouseEvent*)
    {
        if(douClick==0)
        {
            mainWindow->setWindowFlags(Qt::Window);
            mainWindow->showFullScreen();
        }
        else
        {
            mainWindow->setWindowFlags(Qt::SubWindow);
            mainWindow->showNormal();
        }

        douClick=~douClick;
    }

private:
    QWidget* mainFrame;
    QWidget* mainWindow;
    bool mousePress;
    int douClick;
    QPoint pressMouseAt,pressMainFrameAt;
};

#endif // TITLE_H
