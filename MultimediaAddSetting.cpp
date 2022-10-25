#include "MultimediaAddSetting.h"
#include <QMutex>

QMutex eof_mut;
EOF_DEAL eof_deal = EOF_STOP;

void setEofDeal(EOF_DEAL ed)
{
    eof_mut.lock();
    eof_deal = ed;
    eof_mut.unlock();
}

EOF_DEAL getEofDeal()
{
    eof_mut.lock();
    EOF_DEAL ed = eof_deal;
    eof_mut.unlock();
    return ed;
}

//------------------------------------------

QMutex hw_sync_mut;
bool hw_sync = true;

void setHWSync(bool b)
{
    hw_sync_mut.lock();
    hw_sync = b;
    hw_sync_mut.unlock();
}

bool isHWSync()
{
    hw_sync_mut.lock();
    bool b = hw_sync;
    hw_sync_mut.unlock();
    return b;
}

//-----------------------------------------

QMutex sleepAtPause_mut;
int sleepAtPause = 20;

void setSleepAtPause(int x)
{
    sleepAtPause_mut.lock();
    sleepAtPause = x;
    sleepAtPause_mut.unlock();
}

int getSleepAtPause()
{
    sleepAtPause_mut.lock();
    int x = sleepAtPause;
    sleepAtPause_mut.unlock();
    return x;
}
