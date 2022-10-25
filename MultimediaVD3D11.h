#ifndef MULTIMEDIAVD3D11_H
#define MULTIMEDIAVD3D11_H

#include <vector>
#include <QWidget>
#include <initguid.h>
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "MultimediaHW.h"
using namespace std;

class VideoD3D11 : public QWidget
{
    Q_OBJECT

public:
    VideoD3D11(QWidget* parent=0);
    void initD3D11(int,int);
    void d3d11va_device_create(AVCodecContext*);
    void freeResourceAndHide();
    bool existDataInCurSwapChain();
    void showInUi();

public:
    void prepare(AVFrame*);
    void present();
    void turnToNextSwapChain();
    void resizeD3D11();

public:
    static int enumAdapters(); 

signals:
    void showFilterNow();
    void hideFilterNow();
    void showInUiNow();
    void hideInUiNow();

private:
    vector<IDXGISwapChain*> swapChains;
    ID3D11Device* d3d11Device;
    ID3D11DeviceContext* d3d11DeviceContext;
    ID3D11VideoDevice* d3d11VideoDevice;
    ID3D11VideoContext* d3d11VideoContext;
    ID3D11VideoProcessorEnumerator* d3d11VideoProcessorEnumerator;
    ID3D11VideoProcessor* d3d11VideoProcessor;

private:
    int videoW, videoH;
    int areaW, areaH;
    int cur_swap_chain_id;
    vector<int> existData;

private:
    void createVideoProcessor();

protected:
    QPaintEngine* paintEngine() const { return NULL; }
};

extern VideoD3D11* videoD3D11;

#endif // MULTIMEDIAVD3D11_H
