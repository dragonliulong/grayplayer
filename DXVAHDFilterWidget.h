#ifndef DXVAHDFILTERWIDGET_H
#define DXVAHDFILTERWIDGET_H

#include <QWidget>
#include <QSlider>
#include "MultimediaFilter.h"

namespace Ui {
class DXVAHDFilterWidget;
}

class DXVAHDFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DXVAHDFilterWidget(QWidget *parent = nullptr);
    ~DXVAHDFilterWidget();

private:
    Ui::DXVAHDFilterWidget *ui;
    bool showFilter;

private:
    void setSlider(QSlider*,DXVAHD_FILTER_RANGE_DATA*);

public slots:
    void showFilterNow();
    void hideFilterNow();
    void setFilterValue();
    void resetSliderAndFilterValue();

protected:
    void paintEvent(QPaintEvent*);
};

#endif // DXVAHDFILTERWIDGET_H
