#ifndef MULTIMEDIAVSDL_H
#define MULTIMEDIAVSDL_H

/* 弃用
#include <QWidget>
#include <QMutex>
#include <QMutexLocker>
#include "MultimediaResource.h"

extern "C"
{
    #include <SDL.h>
}

#undef main  //不使用SDL作为程序入口，取消SDL_main.h中的main定义 ( #define main SDL_main )

class VideoSDL : public QWidget
{
    Q_OBJECT

public:
    VideoSDL(QWidget* parent = 0);
    ~VideoSDL();

public:
    void initSDL(int,int);
    void prepare(AVFrame*);
    void present();
    void resizeSDL();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

private:
    int videoW, videoH;
    int areaW, areaH;
    bool resizeFlag;
    QMutex mut;

protected:
    void resizeEvent(QResizeEvent*);
};

extern VideoSDL* videoSDL;
*/

#endif // MULTIMEDIAVSDL_H
