#ifndef STANDARDITEM_H
#define STANDARDITEM_H

#include <QStandardItem>
#include <QFileInfo>
#include "MultimediaType.h"
#include <string>
#include <QDebug>
using namespace std;

class StandardItem : public QStandardItem
{
public:
    StandardItem() : QStandardItem() {}

    StandardItem(QString& file, const int w = 20) : QStandardItem()
    {
        setEditable(false);
        setSizeHint(QSize(0,35));
        setFont(QFont("微软雅黑",9));

        fileName = file;
        getInfo(file);

        QString tip;
        insert(file, tip, w);
        setToolTip(tip);
    }

    MultimediaType getType()
    {
        return type;
    }

    QString getFileName()
    {
        return fileName;
    }

private:
    void insert(QString& t0, QString& t1, const int w)
    {
        int j = 0;

        for(int i=0; i < t0.size() ;i++)
        {
            j++;
            t1.push_back(t0[i]);

            if(j >= w)
            {
                j = 0;
                t1.push_back('\n');
            }
        }
    }

    void getInfo(QString& file)
    {
        QFileInfo fileInfo(file);
        string suf = fileInfo.suffix().toStdString();
        setText(fileInfo.fileName());

        if(isAudioType[suf]) type = AUDIO_TYPE;
        else if(isVideoType[suf]) type = VIDEO_TYPE;
        else type = UNKNOW_TYPE;

        if(type == AUDIO_TYPE) setForeground(QColor(0,255,255,180));
        else if(type == VIDEO_TYPE) setForeground(QColor(0,255,0,180));
        else setForeground(QColor(180,180,180));
    }

private:
    MultimediaType type;
    QString fileName;
};

#endif // STANDARDITEM_H
