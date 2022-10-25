#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include <QWidget>

namespace Ui {
class SystemWidget;
}

class SystemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemWidget(QWidget *parent = nullptr);
    ~SystemWidget();

public slots:
    void eofDealChange(int index);

private:
    Ui::SystemWidget *ui;
};

#endif // SYSTEMWIDGET_H
