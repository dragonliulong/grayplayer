#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include "FramelessWidget.h"
#include "Button.h"
#include "SettingLabel.h"
#include "AboutWidget.h"
#include "CoderWidget.h"
#include "DecodeWidget.h"
#include "D3D11VAFilterWidget.h"
#include "DXVAHDFilterWidget.h"
#include "AdditionWidget.h"
#include "SystemWidget.h"
#include <QLabel>
#include <map>
using namespace std;

namespace Ui {
class SettingWidget;
}

class SettingWidget : public FramelessWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget* parent = nullptr);
    ~SettingWidget();
    void follow(QWidget*);
    D3D11VAFilterWidget* getD3D11VAFilterWidget();
    DXVAHDFilterWidget* getDXVAHDFilterWidget();

public slots:
    void showFollow();
    void triggerChecked(SettingLabel*);
    void cancelChecked(SettingLabel*);

private:
    Ui::SettingWidget* ui;
    Button* exit;
    QWidget* followWidget;

private:
    map<QLabel*,QWidget*> to;
    SettingLabel* curLabel;
    DecodeWidget* decodeWidget;
    DXVAHDFilterWidget* dxvahdFilterWidget;
    D3D11VAFilterWidget* d3d11vaFilterWidget;
    AboutWidget* aboutWidget;
    CoderWidget* coderWidget;
    AdditionWidget* additionWidget;
    SystemWidget* systemWidget;

protected:
    void paintEvent(QPaintEvent*);
};

#endif // SETTINGWIDGET_H
