#ifndef D3D11VAFILTERWIDGET_H
#define D3D11VAFILTERWIDGET_H

#include <QWidget>
#include <QSlider>
#include "MultimediaFilter.h"

namespace Ui {
class D3D11VAFilterWidget;
}

class D3D11VAFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit D3D11VAFilterWidget(QWidget *parent = nullptr);
    ~D3D11VAFilterWidget();

private:
    Ui::D3D11VAFilterWidget *ui;
    bool showFilter;

private:
    void setSlider(QSlider*,D3D11_VIDEO_PROCESSOR_FILTER_RANGE*);

public slots:
    void showFilterNow();
    void hideFilterNow();
    void setFilterValue();
    void resetSliderAndFilterValue();

protected:
    void paintEvent(QPaintEvent*);
};

#endif // D3D11VAFILTERWIDGET_H
