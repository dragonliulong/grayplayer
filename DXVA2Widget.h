#ifndef DXVA2WIDGET_H
#define DXVA2WIDGET_H

#include <QWidget>

namespace Ui {
class DXVA2Widget;
}

class DXVA2Widget : public QWidget
{
    Q_OBJECT

public:
    explicit DXVA2Widget(QWidget *parent = nullptr);
    ~DXVA2Widget();
    bool isChecked();
    void setFromDefault();

private:
    Ui::DXVA2Widget *ui;
};

#endif // DXVA2WIDGET_H
