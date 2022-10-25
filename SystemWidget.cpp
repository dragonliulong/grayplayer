#include "SystemWidget.h"
#include "ui_SystemWidget.h"
#include "MultimediaAddSetting.h"
#include <QSettings>

SystemWidget::SystemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemWidget)
{
    ui->setupUi(this);

    connect(ui->eof_deal,SIGNAL(currentIndexChanged(int)),this,SLOT(eofDealChange(int)));

    QString path = QCoreApplication::applicationDirPath() + "/systemSetting.ini";
    QSettings setting(path, QSettings::IniFormat);
    ui->eof_deal->setCurrentIndex(setting.value("general/eof_deal", 0).toInt());
    setEofDeal((EOF_DEAL)ui->eof_deal->currentIndex());
}

SystemWidget::~SystemWidget()
{
    delete ui;
}

void SystemWidget::eofDealChange(int index)
{
    QString path = QCoreApplication::applicationDirPath() + "/systemSetting.ini";
    QSettings setting(path, QSettings::IniFormat);
    setting.setValue("general/eof_deal", index);
    setEofDeal((EOF_DEAL)index);
}
