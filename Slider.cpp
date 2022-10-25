#include "Slider.h"

Color Slider::handleColor={250,250,250};
Color Slider::addPageColor={20,40,60};
Color Slider::subPageColor={60,60,255};

QVariant Slider::StyleInterpolator(const SliderStyle& f,const SliderStyle& t,qreal progress)
{
    SliderStyle res;

    int groH = f.groove.height +(t.groove.height - f.groove.height)*progress;
    int rad = f.handle.radius + (t.handle.radius - f.handle.radius)*progress;

    res.SetGroove(groH, 0, 0);
    res.SetHandle(2*rad, rad, -rad, -rad, -(rad-groH/2), -(rad-groH/2), handleColor);
    res.SetAddPage(addPageColor);
    res.SetSubPage(subPageColor);

    QVariant v;
    v.setValue(res);
    return v;
}
