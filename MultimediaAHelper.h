#ifndef MULTIMEDIAAHELPER_H
#define MULTIMEDIAAHELPER_H

#include <QLabel>
#include <QMutex>
#include "MultimediaResource.h"

class AudioHelper : public QWidget
{
    Q_OBJECT

public:
    AudioHelper(QWidget* p=0);
    void resizeHelper();
    void freeResourceAndHide();

signals:
    void showInUi();
    void hideInUi();

public slots:
    void setImage(char*);

private:
    void decodeAndSet();
    AVPixelFormat convertDeprecatedFormat(enum AVPixelFormat format);

private:
    AVFormatContext* fmtCtx;
    AVCodecContext* codecCtx;
    AVCodec* codec;
    uint8_t* buffer;

private:
    QImage image;
    QMutex mut, img_mut;

private:
    bool isImageNull();

protected:
    void paintEvent(QPaintEvent*);
};

extern AudioHelper* audioHelper;

#endif // MULTIMEDIAAHELPER_H
