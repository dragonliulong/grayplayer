#ifndef ADDITIONWIDGET_H
#define ADDITIONWIDGET_H

#include <QWidget>
#include "ExplainWidget.h"

namespace Ui {
class AdditionWidget;
}

class AdditionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdditionWidget(QWidget *parent = nullptr);
    ~AdditionWidget();

public slots:
    void hwSyncCheck(bool);
    void sleepAtPauseChange(int);
    void showExplain();

private:
    Ui::AdditionWidget *ui;
    ExplainWidget* explainWidget;
};

#endif // ADDITIONWIDGET_H
