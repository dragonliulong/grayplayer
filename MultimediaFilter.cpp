#include "MultimediaFilter.h"
#include <QMutex>

QMutex d3d11va_filter_mut;
D3D11VAFilter d3d11vaFilter;
D3D11VAFilterRange d3d11vaFilterRange;

void setD3D11VAFilter(D3D11VAFilter* pf)
{
    d3d11va_filter_mut.lock();

    if(pf)
    {
        d3d11vaFilter.brightness = pf->brightness;
        d3d11vaFilter.contrast = pf->contrast;
        d3d11vaFilter.hue = pf->hue;
        d3d11vaFilter.saturation = pf->saturation;
        d3d11vaFilter.edge_enhancement = pf->edge_enhancement;
    }

    d3d11va_filter_mut.unlock();
}

D3D11VAFilter getD3D11VAFilter()
{
    d3d11va_filter_mut.lock();
    D3D11VAFilter filter = d3d11vaFilter;
    d3d11va_filter_mut.unlock();
    return filter;
}

void setD3D11VAFilterRange(D3D11VAFilterRange* r)
{
    d3d11va_filter_mut.lock();

    if(r)
    {
        d3d11vaFilterRange.brightness_range = r->brightness_range;
        d3d11vaFilterRange.contrast_range = r->contrast_range;
        d3d11vaFilterRange.hue_range = r->hue_range;
        d3d11vaFilterRange.saturation_range = r->saturation_range;
        d3d11vaFilterRange.edge_enhancement_range = r->edge_enhancement_range;
    }

    d3d11va_filter_mut.unlock();
}

D3D11VAFilterRange getD3D11VAFilterRange()
{
    d3d11va_filter_mut.lock();
    D3D11VAFilterRange range = d3d11vaFilterRange;
    d3d11va_filter_mut.unlock();
    return range;
}

//-----------------------------------------------------------------------------------------

QMutex dxvahd_filter_mut;
DXVAHDFilter dxvahdFilter;
DXVAHDFilterRange dxvahdFilterRange;

void setDXVAHDFilter(DXVAHDFilter* pf)
{
    dxvahd_filter_mut.lock();

    if(pf)
    {
        dxvahdFilter.brightness = pf->brightness;
        dxvahdFilter.contrast = pf->contrast;
        dxvahdFilter.hue = pf->hue;
        dxvahdFilter.saturation = pf->saturation;
        dxvahdFilter.edge_enhancement = pf->edge_enhancement;
    }

    dxvahd_filter_mut.unlock();
}

DXVAHDFilter getDXVAHDFilter()
{
    dxvahd_filter_mut.lock();
    DXVAHDFilter filter = dxvahdFilter;
    dxvahd_filter_mut.unlock();
    return filter;
}

void setDXVAHDFilterRange(DXVAHDFilterRange* r)
{
    dxvahd_filter_mut.lock();

    if(r)
    {
        dxvahdFilterRange.brightness_range = r->brightness_range;
        dxvahdFilterRange.contrast_range = r->contrast_range;
        dxvahdFilterRange.hue_range = r->hue_range;
        dxvahdFilterRange.saturation_range = r->saturation_range;
        dxvahdFilterRange.edge_enhancement_range = r->edge_enhancement_range;
    }

    dxvahd_filter_mut.unlock();
}

DXVAHDFilterRange getDXVAHDFilterRange()
{
    dxvahd_filter_mut.lock();
    DXVAHDFilterRange range = dxvahdFilterRange;
    dxvahd_filter_mut.unlock();
    return range;
}
