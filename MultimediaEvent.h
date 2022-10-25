#ifndef MULTIMEDIAEVENT_H
#define MULTIMEDIAEVENT_H

#include <queue>
using namespace std;

enum MultimediaEventType
{
    PAUSE_EVENT,
    SPEED_EVENT,
    STOP_EVENT,
    SKIP_EVENT,
    SlIDER_PRESS_EVENT,
    SLIDER_RELEASE_EVENT,
    FULLSCREEN_EVENT
};

struct MultimediaEvent
{
    int type;
    double val;
    bool can_give_up;
};

//----------------------------------------------------------------------

bool is_audio_decode_event_empty();
MultimediaEvent get_audio_decode_event_front();
void push_audio_decode_event(MultimediaEvent);
void pop_audio_decode_event();

bool is_video_decode_event_empty();
MultimediaEvent get_video_decode_event_front();
void push_video_decode_event(MultimediaEvent);
void pop_video_decode_event();

//------------------------------------------------------------------------------

bool is_audio_play_event_empty();
MultimediaEvent get_audio_play_event_front();
void push_audio_play_event(MultimediaEvent);
void pop_audio_play_event();

bool is_video_play_event_empty();
MultimediaEvent get_video_play_event_front();
void push_video_play_event(MultimediaEvent);
void pop_video_play_event();

//-------------------------------------------------------------------------------

#endif // MULTIMEDIAEVENT_H
