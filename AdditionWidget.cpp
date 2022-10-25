#include "AdditionWidget.h"
#include "ui_AdditionWidget.h"
#include "MultimediaAddSetting.h"

AdditionWidget::AdditionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdditionWidget)
{
    ui->setupUi(this);
    explainWidget = new ExplainWidget();
    explainWidget->setType(HW_SYNC_EXPLAIN);

    connect(ui->hw_sync,&QCheckBox::clicked,this,&AdditionWidget::hwSyncCheck);
    connect(ui->sleepAtPause,SIGNAL(valueChanged(int)),this,SLOT(sleepAtPauseChange(int)));
    connect(ui->explain,&QPushButton::clicked,this,&AdditionWidget::showExplain);

    ui->sleepAtPause->setValue(20);
}

void AdditionWidget::hwSyncCheck(bool b)
{
    setHWSync(!b);
}

void AdditionWidget::showExplain()
{
    int x = (parentWidget()->width() - explainWidget->width())/2 + parentWidget()->x();
    int y = (parentWidget()->height() - explainWidget->height())/2 + parentWidget()->y();

    explainWidget->move(x,y);
    explainWidget->show();
}

void AdditionWidget::sleepAtPauseChange(int x)
{
    setSleepAtPause(x);
}

AdditionWidget::~AdditionWidget()
{
    delete ui;
}
