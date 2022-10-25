#include "Button.h"
#include <QMouseEvent>

ColorA Button::IncColorA(const ColorA& c,int x,int y,int z,double t)
{ return { c.r+x, c.g+y, c.b+z, c.a+t }; }

QVariant Button::ColorInterpolator(const ButtonColor& f,const ButtonColor& t,qreal progress)
{
    ButtonColor res;

    res.BackGroundColor=IncColorA(f.BackGroundColor,
                                   (t.BackGroundColor.r-f.BackGroundColor.r)*progress,
                                   (t.BackGroundColor.g-f.BackGroundColor.g)*progress,
                                   (t.BackGroundColor.b-f.BackGroundColor.b)*progress,
                                   (t.BackGroundColor.a-f.BackGroundColor.a)*progress);

    res.TextColor=IncColorA(f.TextColor,
                             (t.TextColor.r-f.TextColor.r)*progress,
                             (t.TextColor.g-f.TextColor.g)*progress,
                             (t.TextColor.b-f.TextColor.b)*progress,
                             (t.TextColor.a-f.TextColor.a)*progress);

    res.BorderColor=IncColorA(f.BorderColor,
                               (t.BorderColor.r-f.BorderColor.r)*progress,
                               (t.BorderColor.g-f.BorderColor.g)*progress,
                               (t.BorderColor.b-f.BorderColor.b)*progress,
                               (t.BorderColor.a-f.BorderColor.a)*progress);

    QVariant v;
    v.setValue(res);
    return v;
}
