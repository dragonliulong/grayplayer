#include "MultimediaType.h"
#include <QMutex>
#include <QFileInfo>

vector<string> audioTypes =
{
    "aac", "ac3", "amr", "cda",
    "dts", "flac", "m1a", "m2a",
    "m4a", "mid", "midi", "mka",
    "mp2", "mp3", "mpa", "ogg",
    "ra", "tak", "tta", "wav",
    "wma", "wv", "acc"
};

vector<string> videoTypes =
{
    //Window媒体
    "asf", "avi", "wm", "wmp",
    "wmv",

    //Real媒体
    "ram", "rm", "rmvb", "rp",
    "rpm", "rt", "smi", "smil",

    //Apple媒体
    "mov", "qt",

    //Flash媒体
    "f4v", "flv", "hlv",

    //MPEG1/2媒体
    "dat", "m1v", "m2p", "m2t",
    "m2ts", "m2v", "mpv2", "mpe",
    "mpeg", "mpg", "mp2v", "pss",
    "pva", "tp", "tpr", "ts",

    //MPEG4媒体
    "m4b", "m4p", "m4v", "mp4",
    "mpeg4",

    //3GPP媒体
    "3g2", "3gp", "3gp2", "3gpp",

    //DVD媒体
    "ifo", "vob",

    //其他视频文件
    "amv", "bik", "csf", "divx",
    "evo", "ivm", "mkv", "mod",
    "mts", "ogm", "pmp", "tod",
    "vp6", "webm", "xlmv", "scm"
};

//--------------------------------------------------------------------

map<string,bool> isAudioType;
map<string,bool> isVideoType;

void initTypeMap()
{
    for(int i=0; i < (int)audioTypes.size(); i++)
        isAudioType[audioTypes[i]] = true;

    for(int i=0; i < (int)videoTypes.size(); i++)
        isVideoType[videoTypes[i]] = true;
}

//----------------------------------------------------------------------

MultimediaType type = UNKNOW_TYPE;
QMutex multimedia_type_mut;

void set_multimedia_type(char* file, MultimediaType* t)
{
    multimedia_type_mut.lock();

    //-----------------------------------------------------

    string fileName = file;
    QFileInfo fileInfo(file);
    string suf = fileInfo.suffix().toStdString();

    if(t == NULL)
    {
        string tmp;

        for(int i=0; i < (int)fileName.size() && fileName[i] != ':'; i++)
            tmp += fileName[i];

        if(tmp == "http" || tmp == "https" || tmp == "rtmp" || tmp == "rtsp")
            type = NETWORK_TYPE;

        if(type == UNKNOW_TYPE && isAudioType[suf]) type = AUDIO_TYPE;
        if(type == UNKNOW_TYPE && isVideoType[suf]) type = VIDEO_TYPE;
    }
    else
    {
        type = *t;
    }

    //-----------------------------------------------------

    multimedia_type_mut.unlock();
}

MultimediaType get_multimedia_type()
{
    multimedia_type_mut.lock();
    MultimediaType t = type;
    multimedia_type_mut.unlock();
    return t;
}
