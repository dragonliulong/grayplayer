#include "DecodeWidget.h"
#include "ui_DecodeWidget.h"
#include "GrayPlayer.h"
#include "MultimediaDecodeSetting.h"
#include <QPainter>
#include <QDebug>
#include <QSettings>

DecodeWidget::DecodeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DecodeWidget),
    curDecodeModeIndex(0)
{
    ui->setupUi(this);

    //----------------------------------------------

    swWidget = new SWWidget(this);
    swWidget->hide();

    dxva2Widget = new DXVA2Widget(this);
    dxva2Widget->hide();

    d3d11vaWidget = new D3D11VAWidget(this);
    d3d11vaWidget->hide();

    to[0] = swWidget;
    to[1] = dxva2Widget;
    to[2] = d3d11vaWidget;

    explainWidget = new ExplainWidget();

    //----------------------------------------------

    connect(ui->decodeMode, SIGNAL(currentIndexChanged(int)), this, SLOT(decodeModeChange(int)));
    connect(ui->save,&QPushButton::clicked,this,&DecodeWidget::saveSetting);
    connect(ui->explain,SIGNAL(clicked()),this,SLOT(showExplain()));
    connect(ui->reset,&QPushButton::clicked,this,&DecodeWidget::resetSetting);

    //---------------------------------------------------------------------------

    curDecodeModeIndex = decodeMode;
    ui->decodeMode->setCurrentIndex(curDecodeModeIndex);
    ui->bottomLayout->addWidget(to[curDecodeModeIndex]);
    to[curDecodeModeIndex]->show();
}

void DecodeWidget::decodeModeChange(int id)
{
    if(to[curDecodeModeIndex])
    {
        ui->bottomLayout->removeWidget(to[curDecodeModeIndex]);
        to[curDecodeModeIndex]->hide();
    }

    if(to[id])
    {
        ui->bottomLayout->addWidget(to[id]);
        to[id]->show();
    }

    curDecodeModeIndex = id;
}

void DecodeWidget::resetSetting()
{
    GrayPlayer::resetDecodeSetting();

    ui->decodeMode->setCurrentIndex(decodeModeDef);
    swWidget->setFromDefault();
    dxva2Widget->setFromDefault();
    d3d11vaWidget->setFromDefault();
}

void DecodeWidget::showExplain()
{
    ExplainType type;

    if(ui->decodeMode->currentIndex() == 0) type = SW_EXPLAIN;
    else if(ui->decodeMode->currentIndex() == 1) type = DXVA2_EXPLAIN;
    else type = D3D11VA_EXPLAIN;

    int x = (parentWidget()->width() - explainWidget->width())/2 + parentWidget()->x();
    int y = (parentWidget()->height() - explainWidget->height())/2 + parentWidget()->y();

    explainWidget->setType(type);
    explainWidget->move(x,y);
    explainWidget->show();
}

DecodeWidget::~DecodeWidget()
{
    delete ui;
}

void DecodeWidget::saveSetting()
{
    QString path = QCoreApplication::applicationDirPath() + "/decodeSetting.ini";
    QSettings setting(path, QSettings::IniFormat);

    setting.setValue("launch/first", false);

    setting.setValue("decode/decodeMode", ui->decodeMode->currentIndex());
    setting.setValue("software/sw_thread_count", swWidget->getThreadCount());
    setting.setValue("d3d11va/adapter_choice", d3d11vaWidget->getAdapterChoice());
    setting.setValue("d3d11va/swap_chain_count", d3d11vaWidget->getSwapChainCount());
    setting.setValue("d3d11va/dxgi_format", d3d11vaWidget->getDXGIFormatIndex());
    setting.setValue("d3d11va/dxgi_swap_effect", d3d11vaWidget->getDXGISwapEffectIndex());
    setting.setValue("dxva2/flipex_mode", dxva2Widget->isChecked());
}

void DecodeWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBrush(QColor(100,100,255));
    painter.setPen(Qt::transparent);
    painter.drawRect(5, ui->decodeMode->y() + ui->decodeMode->height() + 12, width() - 10, 2);

    painter.setPen(Qt::red);
    painter.setFont(QFont("微软雅黑",10));
    painter.drawText(ui->save->x() - 225, ui->save->y() + 25, "注意: 保存后重启程序生效");
}
