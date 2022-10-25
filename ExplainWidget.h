#ifndef EXPLAINWIDGET_H
#define EXPLAINWIDGET_H

#include "FramelessWidget.h"
#include <QPainter>
#include <QDebug>
#include "Button.h"

enum ExplainType
{
    SW_EXPLAIN,
    DXVA2_EXPLAIN,
    D3D11VA_EXPLAIN,
    HW_SYNC_EXPLAIN
};

class ExplainWidget : public FramelessWidget
{
    Q_OBJECT

public:
    ExplainWidget(QWidget* p=0) : FramelessWidget(p)
    {
        setTitleH(60);
        setAttribute(Qt::WA_ShowModal);
        setStyleSheet(styleSheet()+"background:rgb(30,30,40);");
        resize(450,300);

        button = new Button(this);
        button->init(EXIT_BUTTON);
        button->resize(45,40);
        button->move(width()-button->width()-12,12);
        button->show();

        connect(button,&Button::clicked,this,&ExplainWidget::hide);
    }

    void setType(ExplainType t)
    {
        type = t;
        update();
    }

private:
    ExplainType type;
    Button* button;

protected:
    void paintEvent(QPaintEvent*)
    {
        int x=15, y=43;

        QPainter p1(this);
        p1.setFont(QFont("微软雅黑",11,100));
        p1.setPen(QColor(240,240,240));

        p1.drawLine(15, 60, width()-30, 60);

        QPainter p2(this);
        p2.setFont(QFont("微软雅黑",10));
        p2.setPen(QColor(210,210,210));

        QRect rect(15,70,width()-30,height()-60);

        if(type == SW_EXPLAIN)
        {
            p1.drawText(x,y,"软解说明");
            p2.drawText(rect,"最大线程数32");
        }
        else if(type == DXVA2_EXPLAIN)
        {
            p1.drawText(x,y,"DXVA2硬解说明");
            p2.drawText(rect,"FLIPEX模式提供更低的CPU占用和更好的性能.");
        }
        else if(type == D3D11VA_EXPLAIN)
        {
            p1.drawText(x,y,"D3D11VA硬解说明");
            p2.drawText(rect,"DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL对Win8及以上操作系统提供支持.\n"
                             "DXGI_SWAP_EFFECT_FLIP_DISCARD对Win10及以上操作系统提供支持.\n"
                             "一般情况下, FLIP模型能提供更好的性能, 但是多交换链模式对于一些高性能独显能提供更好的性能.\n"
                             "注意: 当交换链数大于1时, 交换效果只支持DXGI_SWAP_EFFECT_DISCARD.(交换链个数最大值8)");
        }
        else
        {
            p1.drawText(x,y,"说明");
            p2.drawText(rect,"关闭硬解时音视频同步: 对于极高分辨率视频(8K及以上), 显卡可能遇到性能瓶颈, 此时音视频同步已经没有意义, "
                             "应该关闭音视频同步(硬解时), 以获取最优性能.");
        }
    }
};

#endif // EXPLAINWIDGET_H
