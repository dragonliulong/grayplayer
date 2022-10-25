#include "DXVA2Widget.h"
#include "ui_DXVA2Widget.h"
#include "MultimediaDecodeSetting.h"

DXVA2Widget::DXVA2Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DXVA2Widget)
{
    ui->setupUi(this);
    ui->flipex_mode->setChecked(flipex_mode);
}

bool DXVA2Widget::isChecked()
{
    return ui->flipex_mode->isChecked();
}

void DXVA2Widget::setFromDefault()
{
    ui->flipex_mode->setChecked(flipex_mode_def);
}

DXVA2Widget::~DXVA2Widget()
{
    delete ui;
}
