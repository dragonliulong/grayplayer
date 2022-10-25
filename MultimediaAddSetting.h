#ifndef MULTIMEDIAADDSETTING_H
#define MULTIMEDIAADDSETTING_H

enum EOF_DEAL
{
    EOF_STOP,
    EOF_PAUSE,
    EOF_REPEAT,
    EOF_NEXT
};

void setEofDeal(EOF_DEAL);
EOF_DEAL getEofDeal();

void setHWSync(bool);
bool isHWSync();

void setSleepAtPause(int);
int getSleepAtPause();

#endif // MULTIMEDIAADDSETTING_H
