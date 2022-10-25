#include "MultimediaEvent.h"
#include <QMutex>

queue<MultimediaEvent> audio_decode_event_queue;
queue<MultimediaEvent> video_decode_event_queue;
queue<MultimediaEvent> audio_play_event_queue;
queue<MultimediaEvent> video_play_event_queue;
QMutex audio_decode_event_mut;
QMutex video_decode_event_mut;
QMutex audio_play_event_mut;
QMutex video_play_event_mut;

//----------------------------------------------------------------

bool is_audio_decode_event_empty()
{
    audio_decode_event_mut.lock();
    bool x=audio_decode_event_queue.empty();
    audio_decode_event_mut.unlock();
    return x;
}

MultimediaEvent get_audio_decode_event_front()
{
    audio_decode_event_mut.lock();
    MultimediaEvent x=audio_decode_event_queue.front();
    audio_decode_event_mut.unlock();
    return x;
}

void push_audio_decode_event(MultimediaEvent x)
{
    audio_decode_event_mut.lock();
    audio_decode_event_queue.push(x);
    audio_decode_event_mut.unlock();
}

void pop_audio_decode_event()
{
    audio_decode_event_mut.lock();
    audio_decode_event_queue.pop();
    audio_decode_event_mut.unlock();
}

//----------------------------------------------------------------------

bool is_video_decode_event_empty()
{
    video_decode_event_mut.lock();
    bool x=video_decode_event_queue.empty();
    video_decode_event_mut.unlock();
    return x;
}

MultimediaEvent get_video_decode_event_front()
{
    video_decode_event_mut.lock();
    MultimediaEvent x=video_decode_event_queue.front();
    video_decode_event_mut.unlock();
    return x;
}

void push_video_decode_event(MultimediaEvent x)
{
    video_decode_event_mut.lock();
    video_decode_event_queue.push(x);
    video_decode_event_mut.unlock();
}

void pop_video_decode_event()
{
    video_decode_event_mut.lock();
    video_decode_event_queue.pop();
    video_decode_event_mut.unlock();
}

//--------------------------------------------------------------------------------

bool is_audio_play_event_empty()
{
    audio_play_event_mut.lock();
    bool x=audio_play_event_queue.empty();
    audio_play_event_mut.unlock();
    return x;
}

MultimediaEvent get_audio_play_event_front()
{
    audio_play_event_mut.lock();
    MultimediaEvent x=audio_play_event_queue.front();
    audio_play_event_mut.unlock();
    return x;
}

void push_audio_play_event(MultimediaEvent x)
{
    audio_play_event_mut.lock();
    audio_play_event_queue.push(x);
    audio_play_event_mut.unlock();
}

void pop_audio_play_event()
{
    audio_play_event_mut.lock();
    audio_play_event_queue.pop();
    audio_play_event_mut.unlock();
}

//------------------------------------------------------------------------------------

bool is_video_play_event_empty()
{
    video_play_event_mut.lock();
    bool x=video_play_event_queue.empty();
    video_play_event_mut.unlock();
    return x;
}

MultimediaEvent get_video_play_event_front()
{
    video_play_event_mut.lock();
    MultimediaEvent x=video_play_event_queue.front();
    video_play_event_mut.unlock();
    return x;
}

void push_video_play_event(MultimediaEvent x)
{
    video_play_event_mut.lock();
    video_play_event_queue.push(x);
    video_play_event_mut.unlock();
}

void pop_video_play_event()
{
    video_play_event_mut.lock();
    video_play_event_queue.pop();
    video_play_event_mut.unlock();
}

//-------------------------------------------------------------------------
