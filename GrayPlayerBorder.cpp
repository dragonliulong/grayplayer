#include "GrayPlayer.h"
#include "ui_GrayPlayer.h"

bool GrayPlayer::isInBorder(Qt::CursorShape& cursorShape)
{
    if(isMaximized()) return false;

    int borW = 10;
    QPoint curAt = mapFromGlobal(QCursor::pos());

    if(curAt.y() < ui->title->y())
    {
        if(curAt.x() < borW)  //左上
        {
            cursorShape = Qt::SizeFDiagCursor;
            basePoint = QPoint(x()+width(), y()+height());
            changeW = true;
            changeH = true;
            changeX = true;
            changeY = true;
            return true;
        }

        if(width() - curAt.x() < borW) //右上
        {
            cursorShape = Qt::SizeBDiagCursor;
            basePoint = QPoint(x(), y()+height());
            changeW = true;
            changeH = true;
            changeX = false;
            changeY = true;
            return true;
        }

        //上
        cursorShape = Qt::SizeVerCursor;
        basePoint = QPoint(0, y()+height());
        changeW = false;
        changeH = true;
        changeX = false;
        changeY = true;
        return true;
    }

    if(height() - curAt.y() < borW)
    {
        if(curAt.x() < borW)  //左下
        {
            cursorShape = Qt::SizeBDiagCursor;
            basePoint = QPoint(x()+width(), y());
            changeW = true;
            changeH = true;
            changeX = true;
            changeY = false;
            return true;
        }

        if(width() - curAt.x() < borW) //右下
        {
            cursorShape = Qt::SizeFDiagCursor;
            basePoint = QPoint(x(), y());
            changeW = true;
            changeH = true;
            changeX = false;
            changeY = false;
            return true;
        }

        //下
        cursorShape = Qt::SizeVerCursor;
        basePoint = QPoint(0, y());
        changeW = false;
        changeH = true;
        changeX = false;
        changeY = false;
        return true;
    }

    if(curAt.x() < borW)  //左
    {
        cursorShape = Qt::SizeHorCursor;
        basePoint = QPoint(x()+width(),0);
        changeW = true;
        changeH = false;
        changeX = true;
        changeY = false;
        return true;
    }

    if(width() - curAt.x() < borW)  //右
    {
        cursorShape = Qt::SizeHorCursor;
        basePoint = QPoint(x(),0);
        changeW = true;
        changeH = false;
        changeX = false;
        changeY = false;
        return true;
    }

    return false;
}
