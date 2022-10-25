#ifndef MULTIMEDIAFILTER_H
#define MULTIMEDIAFILTER_H

#include "MultimediaVD3D11.h"
#include "MultimediaVD3D9.h"

//--------------------------D3D11VA滤镜--------------------------

struct D3D11VAFilter
{
    int brightness;  //亮度
    int contrast;  //对比度
    int hue;  //色调
    int saturation;  //饱和度
    int edge_enhancement;  //边缘增强
};

struct D3D11VAFilterRange
{
    D3D11_VIDEO_PROCESSOR_FILTER_RANGE brightness_range;
    D3D11_VIDEO_PROCESSOR_FILTER_RANGE contrast_range;
    D3D11_VIDEO_PROCESSOR_FILTER_RANGE hue_range;
    D3D11_VIDEO_PROCESSOR_FILTER_RANGE saturation_range;
    D3D11_VIDEO_PROCESSOR_FILTER_RANGE edge_enhancement_range;
};

void setD3D11VAFilter(D3D11VAFilter*);
D3D11VAFilter getD3D11VAFilter();

void setD3D11VAFilterRange(D3D11VAFilterRange*);
D3D11VAFilterRange getD3D11VAFilterRange();

//---------------------------DXVAHD滤镜-------------------------

struct DXVAHDFilter
{
    int brightness;  //亮度
    int contrast;  //对比度
    int hue;  //色调
    int saturation;  //饱和度
    int edge_enhancement;  //边缘增强
};

struct DXVAHDFilterRange
{
    DXVAHD_FILTER_RANGE_DATA brightness_range;
    DXVAHD_FILTER_RANGE_DATA contrast_range;
    DXVAHD_FILTER_RANGE_DATA hue_range;
    DXVAHD_FILTER_RANGE_DATA saturation_range;
    DXVAHD_FILTER_RANGE_DATA edge_enhancement_range;
};

void setDXVAHDFilter(DXVAHDFilter*);
DXVAHDFilter getDXVAHDFilter();

void setDXVAHDFilterRange(DXVAHDFilterRange*);
DXVAHDFilterRange getDXVAHDFilterRange();

#endif // MULTIMEDIAFILTER_H
