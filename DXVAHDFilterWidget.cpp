#include "DXVAHDFilterWidget.h"
#include "ui_DXVAHDFilterWidget.h"
#include <QPainter>

DXVAHDFilterWidget::DXVAHDFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DXVAHDFilterWidget),
    showFilter(false)
{
    ui->setupUi(this);

    connect(ui->brightness,&QSlider::valueChanged,this,&DXVAHDFilterWidget::setFilterValue);
    connect(ui->contrast,&QSlider::valueChanged,this,&DXVAHDFilterWidget::setFilterValue);
    connect(ui->hue,&QSlider::valueChanged,this,&DXVAHDFilterWidget::setFilterValue);
    connect(ui->saturation,&QSlider::valueChanged,this,&DXVAHDFilterWidget::setFilterValue);
    connect(ui->edge_enhancement,&QSlider::valueChanged,this,&DXVAHDFilterWidget::setFilterValue);
    connect(ui->reset,&QPushButton::clicked,this,&DXVAHDFilterWidget::resetSliderAndFilterValue);

    ui->widget->hide();
}

DXVAHDFilterWidget::~DXVAHDFilterWidget()
{
    delete ui;
}

void DXVAHDFilterWidget::paintEvent(QPaintEvent*)
{
    if(!showFilter)
    {
        QPainter painter(this);
        painter.setPen(Qt::black);
        painter.setFont(QFont("微软雅黑",10));
        painter.drawText(80,200,"请使用DXVA2硬解, 并播放视频");
    }
}

void DXVAHDFilterWidget::setFilterValue()
{
    DXVAHDFilter filter;

    filter.brightness = ui->brightness->value();
    filter.contrast = ui->contrast->value();
    filter.hue = ui->hue->value();
    filter.saturation = ui->saturation->value();
    filter.edge_enhancement = ui->edge_enhancement->value();

    setDXVAHDFilter(&filter);
}

void DXVAHDFilterWidget::showFilterNow()
{
    showFilter = true;
    update();

    resetSliderAndFilterValue();
    ui->widget->show();
}

void DXVAHDFilterWidget::hideFilterNow()
{
    showFilter = false;
    update();
    ui->widget->hide();
}

void DXVAHDFilterWidget::setSlider(QSlider* s, DXVAHD_FILTER_RANGE_DATA* r)
{
    s->setMinimum(r->Minimum);
    s->setMaximum(r->Maximum);
    s->setValue(r->Default);
}

void DXVAHDFilterWidget::resetSliderAndFilterValue()
{
    DXVAHDFilterRange filterRange = getDXVAHDFilterRange();

    setSlider(ui->brightness, &filterRange.brightness_range);
    setSlider(ui->contrast, &filterRange.contrast_range);
    setSlider(ui->hue, &filterRange.hue_range);
    setSlider(ui->saturation, &filterRange.saturation_range);
    setSlider(ui->edge_enhancement, &filterRange.edge_enhancement_range);

    DXVAHDFilter filter;

    filter.brightness = filterRange.brightness_range.Default;
    filter.contrast = filterRange.contrast_range.Default;
    filter.hue = filterRange.hue_range.Default;
    filter.saturation = filterRange.saturation_range.Default;
    filter.edge_enhancement = filterRange.edge_enhancement_range.Default;

    setDXVAHDFilter(&filter);
}

