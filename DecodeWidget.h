#ifndef DECODEWIDGET_H
#define DECODEWIDGET_H

#include <QWidget>
#include "D3D11VAWidget.h"
#include "SWWidget.h"
#include "DXVA2Widget.h"
#include "ExplainWidget.h"
#include <map>
using namespace std;

namespace Ui {
class DecodeWidget;
}

class DecodeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DecodeWidget(QWidget *parent = nullptr);
    ~DecodeWidget();

public slots:
    void decodeModeChange(int);
    void saveSetting();
    void resetSetting();
    void showExplain();

private:
    Ui::DecodeWidget *ui;
    ExplainWidget* explainWidget;
    DXVA2Widget* dxva2Widget;
    D3D11VAWidget* d3d11vaWidget;
    SWWidget* swWidget;
    int curDecodeModeIndex;
    map<int, QWidget*> to;

protected:
    void paintEvent(QPaintEvent*);
};

#endif // DECODEWIDGET_H
