#include "GrayPlayer.h"
#include "ui_GrayPlayer.h"
#include <windows.h>
#include <dwmapi.h>
#include <windowsx.h>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QScreen>
#include <cmath>

#define max(x,y) x>y ? x:y
#define min(x,y) x<y ? x:y
#define limit1(x,min,max) x>=min && x<=max
#define limit2(x,min,max) x>min && x<max

void GrayPlayer::mouseDoubleClickEvent(QMouseEvent* e)
{
    if(e->button() != Qt::LeftButton) return;
    bool in_title = limit2(e->y(), 0, ui->videoArea->y());
    if( in_title ) showMaxOrNormal();
}

void GrayPlayer::mousePressEvent(QMouseEvent* e)
{
    if(e->button() != Qt::LeftButton) return;
    leftButtonPress = true;
    pressMouseAt = QCursor::pos();
    pressThisAt = this->pos();
}

void GrayPlayer::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() != Qt::LeftButton) return;
    leftButtonPress = false;
    stretching = false;

    //重新设置鼠标形状
    Qt::CursorShape cursorShape;

    if(isInBorder(cursorShape)) setCursor(cursorShape);
    else setCursor(Qt::ArrowCursor);
}

void GrayPlayer::mouseMoveEvent(QMouseEvent* e)
{
    Qt::CursorShape cursorShape;
    bool in_title = limit2(e->y(), 0, ui->videoArea->y());

    if(stretching)
    {
        int W = changeW ? abs(QCursor::pos().x() - basePoint.x()) : width();
        int H = changeH ? abs(QCursor::pos().y() - basePoint.y()) : height();

        W = max(minimumWidth(), W);
        H = max(minimumHeight(), H);

        int X = changeX ? abs(basePoint.x() - W) : x();
        int Y = changeY ? abs(basePoint.y() - H) : y();

        setGeometry(X, Y, W, H);

        goto end;
    }

    if(isInBorder(cursorShape))
    {
        setCursor(cursorShape);

        if(leftButtonPress)
            stretching = true;

        goto end;
    }

    if(in_title && !isMaximized() && leftButtonPress)
    {
        int dx = QCursor::pos().x() - pressMouseAt.x();
        int dy = QCursor::pos().y() - pressMouseAt.y();

        move(pressThisAt.x() + dx, pressThisAt.y() + dy);
    }

    setCursor(Qt::ArrowCursor);

end:
    QMainWindow::mouseMoveEvent(e);
}

//--------------------------------------------------------------------------------------------

bool GrayPlayer::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
    MSG* msg = static_cast<MSG*>(message);

    if(msg->message == WM_NCCALCSIZE)
    {
        if(msg->wParam)
        {
            QRect availRect = QGuiApplication::screens().at(0)->availableGeometry();

            int leftBor = availRect.x();
            int rightBor = leftBor + availRect.width();
            int topBor = availRect.y();
            int bottomBor = topBor + availRect.height();

            NCCALCSIZE_PARAMS* par = (NCCALCSIZE_PARAMS*)msg->lParam;

            if(par->rgrc[0].left < leftBor && par->rgrc[0].right > rightBor)
            {
                par->rgrc[0].left = leftBor;
                par->rgrc[0].right = rightBor;
            }

            if(par->rgrc[0].top < topBor && par->rgrc[0].bottom > bottomBor)
            {
                par->rgrc[0].top = topBor;
                par->rgrc[0].bottom = bottomBor;
            }
        }

        return true;
    }

    return QMainWindow::nativeEvent(eventType, message, result);
}

void GrayPlayer::resizeEvent(QResizeEvent *)
{
    emit resizeNow();
}
