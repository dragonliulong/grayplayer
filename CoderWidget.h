#ifndef CODERWIDGET_H
#define CODERWIDGET_H

#include <QWidget>

namespace Ui {
class CoderWidget;
}

class CoderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CoderWidget(QWidget *parent = nullptr);
    ~CoderWidget();

private:
    Ui::CoderWidget *ui;
};

#endif // CODERWIDGET_H
