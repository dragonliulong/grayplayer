#include "MultimediaAHelper.h"
#include "MultimediaInterrupt.h"
#include <QThread>
#include <QPainter>
#include <QPainterPath>

AudioHelper::AudioHelper(QWidget* p) : QWidget(p)
{
    fmtCtx=NULL;
    codecCtx=NULL;
    codec=NULL;
    buffer=NULL;

    connect(this,&AudioHelper::showInUi,this,&AudioHelper::show);
    connect(this,&AudioHelper::hideInUi,this,&AudioHelper::hide);

    setMouseTracking(true);  //鼠标监控
    hide();  //隐藏
}

void AudioHelper::freeResourceAndHide()
{
    img_mut.lock();
    image = QImage();
    img_mut.unlock();

    avformat_close_input(&fmtCtx);
    avformat_free_context(fmtCtx);
    avcodec_free_context(&codecCtx);
    av_free(buffer);

    fmtCtx=NULL;
    codecCtx=NULL;
    codec=NULL;
    buffer=NULL;

    emit hideInUi();  //隐藏
}

void AudioHelper::setImage(char* file)
{
    bool beh = false;

    if(file)
    {
        fmtCtx = GetFormatCtx(file);

        if(fmtCtx)
        {
            codec = avcodec_find_decoder(fmtCtx->streams[get_video_id()]->codecpar->codec_id);
            codecCtx = avcodec_alloc_context3(codec);
            codecCtx->pkt_timebase = fmtCtx->streams[get_video_id()]->time_base;
            avcodec_parameters_to_context(codecCtx, fmtCtx->streams[get_video_id()]->codecpar);
            avcodec_open2(codecCtx, codec, NULL);

            mut.lock();
            decodeAndSet();
            mut.unlock();

            beh = true;
        }
    }
    else if(!get_interrupt_flag())
    {
        img_mut.lock();
        image = QImage(); //构造空图像
        img_mut.unlock();

        beh = true;
    }

    if(beh)
    {
        //更新并显示
        resizeHelper();
        update();
        emit showInUi();
    }
}

void AudioHelper::decodeAndSet()
{
    //分配packet, frame, frameRGB
    AVPacket* packet = av_packet_alloc();
    AVFrame* frame = av_frame_alloc();
    AVFrame* frameRGB = av_frame_alloc();

    int w = fmtCtx->streams[get_video_id()]->codecpar->width;
    int h = fmtCtx->streams[get_video_id()]->codecpar->height;

    while(av_read_frame(fmtCtx, packet) >= 0)
    {
        if(packet->stream_index == get_video_id())
        {
            avcodec_send_packet(codecCtx, packet);

            if(avcodec_receive_frame(codecCtx, frame) == 0)
            {
                int buffer_size = av_image_get_buffer_size(AV_PIX_FMT_RGB32, w, h, 1);

                //分配buffer
                buffer = (uint8_t*)av_malloc(buffer_size);
                av_image_fill_arrays(frameRGB->data, frameRGB->linesize, buffer, AV_PIX_FMT_RGB32, w, h, 1);

                //分配设置swsCtx
                SwsContext* swsCtx = sws_getContext(w, h, convertDeprecatedFormat((AVPixelFormat)frame->format),
                                                    w, h, AV_PIX_FMT_RGB32, SWS_FAST_BILINEAR, NULL, NULL, NULL);

                //转换到frameRGB (buffer)
                sws_scale(swsCtx, frame->data, frame->linesize, 0, h, frameRGB->data, frameRGB->linesize);

                img_mut.lock();
                //重新赋值image
                image = QImage((uchar*)buffer, w, h, QImage::Format_RGB32);
                img_mut.unlock();

                //释放swsCtx
                sws_freeContext(swsCtx);

                break;
            }
        }

        //重置packet
        av_packet_unref(packet);
    }

    //释放packet, frame, frameRGB
    av_packet_free(&packet);
    av_frame_free(&frame);
    av_frame_free(&frameRGB);
}

AVPixelFormat AudioHelper::convertDeprecatedFormat(AVPixelFormat format)
{
    switch (format)
    {
    case AV_PIX_FMT_YUVJ420P:
        return AV_PIX_FMT_YUV420P;
        break;
    case AV_PIX_FMT_YUVJ422P:
        return AV_PIX_FMT_YUV422P;
        break;
    case AV_PIX_FMT_YUVJ444P:
        return AV_PIX_FMT_YUV444P;
        break;
    case AV_PIX_FMT_YUVJ440P:
        return AV_PIX_FMT_YUV440P;
        break;
    default:
        return format;
        break;
    }
}

bool AudioHelper::isImageNull()
{
    img_mut.lock();
    bool is = image.isNull();
    img_mut.unlock();
    return is;
}

void AudioHelper::resizeHelper()
{
    if(!parentWidget()) return ;
    if(parentWidget()->width() == width() && parentWidget()->height() == height()) return;
    resize(parentWidget()->width(), parentWidget()->height());
}

void AudioHelper::paintEvent(QPaintEvent* e)
{
    if(mut.tryLock())
    {
        QPainter painter(this);
        painter.setBrush(QColor(30,30,35));
        painter.drawRect(0,0,width(),height());

        int w=300, h=300;
        int x=(width()-w)/2, y=(height()-h)/2;
        QRect rect(x,y,w,h);

        if(isImageNull())
        {
            painter.setPen(QColor(30,30,35));
            painter.setBrush(QColor(20,20,20));
            painter.drawEllipse(rect);

            painter.setFont(QFont("微软雅黑",20));

            painter.setPen(QColor(200,0,0));
            painter.drawText(x+100,y+163, "M");

            painter.setPen(QColor(0,200,0));
            painter.drawText(x+134,y+160, "u");

            painter.setPen(QColor(0,0,200));
            painter.drawText(x+157,y+160, "s");

            painter.setPen(QColor(200,0,200));
            painter.drawText(x+177,y+160, "i");

            painter.setPen(QColor(0,200,200));
            painter.drawText(x+190,y+160, "c");
        }
        else
        {
            QPainterPath path;
            path.addRoundedRect(rect, w/2, h/2);

            painter.setRenderHint(QPainter::Antialiasing);
            painter.setClipPath(path);

            img_mut.lock();
            painter.drawImage(rect, image.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            img_mut.unlock();
        }

        //解锁
        mut.unlock();
    }

    QWidget::paintEvent(e);
}

//showHelper
AudioHelper* audioHelper=NULL;
