#include "D3D11VAWidget.h"
#include <QStandardItem>
#include "ui_D3D11VAWidget.h"
#include "MultimediaDecodeSetting.h"
#include <QDebug>

D3D11VAWidget::D3D11VAWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::D3D11VAWidget)
{
    ui->setupUi(this);

    //先连接信号与槽
    connect(ui->d3d11SwapChainCount,SIGNAL(valueChanged(int)),this,SLOT(swapChainCountChange(int)));
    connect(ui->d3d11SwapEffect,SIGNAL(currentIndexChanged(int)),this,SLOT(swapEffectChange(int)));

    //---------------------------------------------------------------

    for(int i=1; i < (int)adapters.size(); i++)
    {
        if(adapters[i])
        {
            DXGI_ADAPTER_DESC desc;
            adapters[i]->GetDesc(&desc);
            QString gpuName = QString("GPU%1 (%2 MB)").arg(i-1).arg(desc.DedicatedVideoMemory/1024/1024);
            ui->d3d11vaAdapter->addItem(gpuName);
        }
    }

    //----------------------------------------------------------------

    ui->d3d11vaAdapter->setCurrentIndex(adapter_choice);
    ui->d3d11SwapChainCount->setValue(swap_chain_count);

    for(int i=0; i<5; i++)
    {
        if(dxgi_format == dxgi_formats[i])
        {
            ui->d3d11Fomat->setCurrentIndex(i);
            break;
        }
    }

    for(int i=0; i<4; i++)
    {
        if(dxgi_swap_effect == dxgi_swap_effects[i])
        {
            ui->d3d11SwapEffect->setCurrentIndex(i);
            break;
        }
    }
}

void D3D11VAWidget::setFromDefault()
{
    ui->d3d11vaAdapter->setCurrentIndex(adapter_choice_def);
    ui->d3d11SwapChainCount->setValue(swap_chain_count_def);

    for(int i=0; i<5; i++)
    {
        if(dxgi_format_def == dxgi_formats[i])
        {
            ui->d3d11Fomat->setCurrentIndex(i);
            break;
        }
    }

    for(int i=0; i<4; i++)
    {
        if(dxgi_swap_effect_def == dxgi_swap_effects[i])
        {
            ui->d3d11SwapEffect->setCurrentIndex(i);
            break;
        }
    }
}

void D3D11VAWidget::swapChainCountChange(int x)
{
    if(x > 1) ui->d3d11SwapEffect->setCurrentIndex(3);
}

void D3D11VAWidget::swapEffectChange(int x)
{
    if(ui->d3d11SwapChainCount->value() > 1 && x!=3)
        ui->d3d11SwapEffect->setCurrentIndex(3);
}

int D3D11VAWidget::getAdapterChoice()
{
    return ui->d3d11vaAdapter->currentIndex();
}

int D3D11VAWidget::getSwapChainCount()
{
    return ui->d3d11SwapChainCount->value();
}

int D3D11VAWidget::getDXGIFormatIndex()
{
    return ui->d3d11Fomat->currentIndex();
}

int D3D11VAWidget::getDXGISwapEffectIndex()
{
    return ui->d3d11SwapEffect->currentIndex();
}

D3D11VAWidget::~D3D11VAWidget()
{
    delete ui;
}
