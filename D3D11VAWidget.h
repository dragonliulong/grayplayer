#ifndef D3D11VAWIDGET_H
#define D3D11VAWIDGET_H

#include <QWidget>
#include <QComboBox>
#include "MultimediaVD3D11.h"

namespace Ui {
class D3D11VAWidget;
}

class D3D11VAWidget : public QWidget
{
    Q_OBJECT

public:
    explicit D3D11VAWidget(QWidget *parent = nullptr);
    ~D3D11VAWidget();

public slots:
    void swapChainCountChange(int);
    void swapEffectChange(int);

public:
    int getAdapterChoice();
    int getSwapChainCount();
    int getDXGIFormatIndex();
    int getDXGISwapEffectIndex();

public:
    void setFromDefault();

private:
    Ui::D3D11VAWidget *ui;
};

#endif // D3D11VAWIDGET_H
