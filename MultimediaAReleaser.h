#ifndef MULTIMEDIAARELEASER_H
#define MULTIMEDIAARELEASER_H

#include <QObject>
#include <QAudioOutput>
#include <QThread>

class AudioReleaser : public QObject
{
    Q_OBJECT

public:
    AudioReleaser();

public slots:
    void releaseAudioOutput(QAudioOutput*);

private:
    QThread* thread;
};

#endif // MULTIMEDIAARELEASER_H
