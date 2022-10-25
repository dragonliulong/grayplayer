#include "MultimediaInterrupt.h"
#include <QMutex>

bool interrupt_flag=false;
QMutex interrupt_mut;

void set_interrupt_flag(bool f)
{
    interrupt_mut.lock();
    interrupt_flag = f;
    interrupt_mut.unlock();
}

bool get_interrupt_flag()
{
    interrupt_mut.lock();
    bool f = interrupt_flag;
    interrupt_mut.unlock();
    return f;
}

//------------------------------------------------------------

int interrupt_callback(void*)
{
    if(get_interrupt_flag()) return 1;
    return 0;
}

void get_interrupt_for(AVFormatContext* fmt)
{
    if(!fmt) return;
    fmt->interrupt_callback.callback = interrupt_callback;
    fmt->interrupt_callback.opaque = NULL;
}

//-----------------------------------------------------------

Interrupter::Interrupter()
{
    thread = new QThread();
    moveToThread(thread);
    thread->start();
}

void Interrupter::setInterruptFlagTrue(int)
{
    set_interrupt_flag(true);
}
