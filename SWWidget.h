#ifndef SWWIDGET_H
#define SWWIDGET_H

#include <QWidget>

namespace Ui {
class SWWidget;
}

class SWWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SWWidget(QWidget *parent = nullptr);
    ~SWWidget();

public:
    void setFromDefault();
    int getThreadCount();

private:
    Ui::SWWidget *ui;
};

#endif // SWWIDGET_H
