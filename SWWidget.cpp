#include "SWWidget.h"
#include "ui_SWWidget.h"
#include "MultimediaDecodeSetting.h"

SWWidget::SWWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SWWidget)
{
    ui->setupUi(this);
    ui->swThreadCount->setValue(sw_thread_count);
}

void SWWidget::setFromDefault()
{
    ui->swThreadCount->setValue(sw_thread_count_def);
}

int SWWidget::getThreadCount()
{
    return ui->swThreadCount->value();
}

SWWidget::~SWWidget()
{
    delete ui;
}
