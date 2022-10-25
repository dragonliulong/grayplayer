#include <QMutex>

bool exit_flag = true;
QMutex exit_mut;

bool get_exit_flag()
{
    exit_mut.lock();
    bool f = exit_flag;
    exit_mut.unlock();
    return f;
}

void set_exit_flag(bool f)
{
    exit_mut.lock();
    exit_flag = f;
    exit_mut.unlock();
}
