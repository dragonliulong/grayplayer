#ifndef MULTIMEDIAINTERRUPT_H
#define MULTIMEDIAINTERRUPT_H

#include "MultimediaResource.h"
#include <QObject>
#include <QThread>

void get_interrupt_for(AVFormatContext*);
void set_interrupt_flag(bool);
bool get_interrupt_flag();

class Interrupter : public QObject
{
    Q_OBJECT

public:
    Interrupter();

public slots:
    void setInterruptFlagTrue(int object=0);

private:
    QThread* thread;
};

#endif // MULTIMEDIAINTERRUPT_H
