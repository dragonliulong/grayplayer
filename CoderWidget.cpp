#include "CoderWidget.h"
#include "ui_CoderWidget.h"

CoderWidget::CoderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoderWidget)
{
    ui->setupUi(this);

    ui->csdnURL->setOpenExternalLinks(true);
    ui->csdnURL->setText(tr("<a href=\"https://blog.csdn.net/qq_35743099?spm=1000.2115.3001.5343\">链接"));

    ui->bilibiliURL->setOpenExternalLinks(true);
    ui->bilibiliURL->setText(tr("<a href=\"https://space.bilibili.com/39783287/\">链接"));

    ui->mailURL->setText("1359316404@qq.com");
    ui->githubURL->setText("?");
}

CoderWidget::~CoderWidget()
{
    delete ui;
}
