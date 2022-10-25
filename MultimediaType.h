#ifndef MULTIMEDIATYPE_H
#define MULTIMEDIATYPE_H

#include <vector>
#include <string>
#include <map>
using namespace std;

enum MultimediaType
{
    AUDIO_TYPE,
    VIDEO_TYPE,
    NETWORK_TYPE,
    UNKNOW_TYPE
};

extern vector<string> audioTypes;
extern vector<string> videoTypes;
extern map<string,bool> isAudioType;
extern map<string,bool> isVideoType;

void set_multimedia_type(char*,MultimediaType*);
MultimediaType get_multimedia_type();
void initTypeMap();

#endif // MULTIMEDIATYPE_H
