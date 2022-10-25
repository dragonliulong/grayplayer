#ifndef FRAMELESSWIDGET_H
#define FRAMELESSWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <windows.h>
#include <dwmapi.h>
#include <windowsx.h>

class FramelessWidget : public QWidget
{
    Q_OBJECT

public:
    FramelessWidget(QWidget* parent=NULL) : QWidget(parent)
    {
        setWindowFlag(Qt::FramelessWindowHint);

        //---------------------------------DWM窗口效果--------------------------------------------

        DWORD style = GetWindowLongPtr((HWND)winId(), GWL_STYLE);
        SetWindowLongPtr((HWND)winId(), GWL_STYLE, style | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);

        BOOL isDwmComEnabled = false;
        DwmIsCompositionEnabled(&isDwmComEnabled);

        if (isDwmComEnabled)
        {
            MARGINS margins =
            {
                .cxLeftWidth = 0,
                .cxRightWidth = 0,
                .cyTopHeight = 1,
                .cyBottomHeight = 1
            };

            DwmExtendFrameIntoClientArea((HWND)winId(), &margins);
        }

        //标题栏高度
        titleH = 0;
    }

    void setTitleH(int h)
    {
        titleH = h;
    }

private:
    bool leftButtonPress;
    QPoint pressMouseAt, pressThisAt;
    int titleH;

protected:
    bool nativeEvent(const QByteArray& eventType, void* message, long* result)
    {
        MSG* msg = static_cast<MSG*>(message);

        if(msg->message == WM_NCCALCSIZE)
            return true;

        return QWidget::nativeEvent(eventType, message, result);
    }

    void mousePressEvent(QMouseEvent* e)
    {
        if(e->button() != Qt::LeftButton) return;
        leftButtonPress = true;
        pressMouseAt = QCursor::pos();
        pressThisAt = this->pos();
    }

    void mouseReleaseEvent(QMouseEvent *e)
    {
        if(e->button() != Qt::LeftButton) return;
        leftButtonPress = false;
    }

    void mouseMoveEvent(QMouseEvent* e)
    {
        if(e->y() < titleH && !isMaximized() && leftButtonPress)
        {
            int dx = QCursor::pos().x() - pressMouseAt.x();
            int dy = QCursor::pos().y() - pressMouseAt.y();

            move(pressThisAt.x() + dx, pressThisAt.y() + dy);
        }

        QWidget::mouseMoveEvent(e);
    }
};

#endif // FRAMELESSWIDGET_H
