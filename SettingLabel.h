#ifndef SETTINGLABEL_H
#define SETTINGLABEL_H

#include <QLabel>
#include <QMouseEvent>

class SettingLabel : public QLabel
{
    Q_OBJECT

public:
    SettingLabel(QWidget* parent = nullptr) : QLabel(parent)
    {
        normalStyle = styleSheet();
        checked = false;
    }

    void triggerChecked()
    {
        if(!checked)
        {
            checked = true;
            setStyleSheet("background:rgb(0,150,255);");
            emit triggerCheckedSignal(this);
        }
    }

    void cancelChecked()
    {
        if(checked)
        {
            checked = false;
            setStyleSheet(normalStyle);
            emit cancelCheckedSignal(this);
        }
    }

private:
    QString normalStyle;
    bool checked;

signals:
    void triggerCheckedSignal(SettingLabel*);
    void cancelCheckedSignal(SettingLabel*);

protected:
    void enterEvent(QEvent*)
    {
        if(checked) return;
        setStyleSheet("background:rgb(210,210,210);");
    }

    void leaveEvent(QEvent*)
    {
        if(checked) return;
        setStyleSheet(normalStyle);
    }

    void mousePressEvent(QMouseEvent* e)
    {
        if(e->button() == Qt::LeftButton)
            triggerChecked();
    }
};

#endif // SETTINGLABEL_H
