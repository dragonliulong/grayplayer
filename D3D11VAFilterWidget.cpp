#include "D3D11VAFilterWidget.h"
#include "ui_D3D11VAFilterWidget.h"
#include <QPainter>
#include <QPushButton>

D3D11VAFilterWidget::D3D11VAFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::D3D11VAFilterWidget),
    showFilter(false)
{
    ui->setupUi(this);

    connect(ui->brightness,&QSlider::valueChanged,this,&D3D11VAFilterWidget::setFilterValue);
    connect(ui->contrast,&QSlider::valueChanged,this,&D3D11VAFilterWidget::setFilterValue);
    connect(ui->hue,&QSlider::valueChanged,this,&D3D11VAFilterWidget::setFilterValue);
    connect(ui->saturation,&QSlider::valueChanged,this,&D3D11VAFilterWidget::setFilterValue);
    connect(ui->edge_enhancement,&QSlider::valueChanged,this,&D3D11VAFilterWidget::setFilterValue);
    connect(ui->reset,&QPushButton::clicked,this,&D3D11VAFilterWidget::resetSliderAndFilterValue);

    ui->widget->hide();
}

D3D11VAFilterWidget::~D3D11VAFilterWidget()
{
    delete ui;
}

void D3D11VAFilterWidget::paintEvent(QPaintEvent*)
{
    if(!showFilter)
    {
        QPainter painter(this);
        painter.setPen(Qt::black);
        painter.setFont(QFont("微软雅黑",10));
        painter.drawText(80,200,"请使用D3D11VA硬解, 并播放视频");
    }
}

void D3D11VAFilterWidget::setFilterValue()
{
    D3D11VAFilter filter;

    filter.brightness = ui->brightness->value();
    filter.contrast = ui->contrast->value();
    filter.hue = ui->hue->value();
    filter.saturation = ui->saturation->value();
    filter.edge_enhancement = ui->edge_enhancement->value();

    setD3D11VAFilter(&filter);
}

void D3D11VAFilterWidget::showFilterNow()
{
    showFilter = true;
    update();

    resetSliderAndFilterValue();
    ui->widget->show();
}

void D3D11VAFilterWidget::hideFilterNow()
{
    showFilter = false;
    update();
    ui->widget->hide();
}

void D3D11VAFilterWidget::setSlider(QSlider* s, D3D11_VIDEO_PROCESSOR_FILTER_RANGE* r)
{
    s->setMinimum(r->Minimum);
    s->setMaximum(r->Maximum);
    s->setValue(r->Default);
}

void D3D11VAFilterWidget::resetSliderAndFilterValue()
{
    D3D11VAFilterRange filterRange = getD3D11VAFilterRange();

    setSlider(ui->brightness, &filterRange.brightness_range);
    setSlider(ui->contrast, &filterRange.contrast_range);
    setSlider(ui->hue, &filterRange.hue_range);
    setSlider(ui->saturation, &filterRange.saturation_range);
    setSlider(ui->edge_enhancement, &filterRange.edge_enhancement_range);

    D3D11VAFilter filter;

    filter.brightness = filterRange.brightness_range.Default;
    filter.contrast = filterRange.contrast_range.Default;
    filter.hue = filterRange.hue_range.Default;
    filter.saturation = filterRange.saturation_range.Default;
    filter.edge_enhancement = filterRange.edge_enhancement_range.Default;

    setD3D11VAFilter(&filter);
}
