#pragma once
#include "SingletonBase.h"

#define g_pPixelManager PixelCollision::GetInstance()

class PixelCollision : public SingletonBase<PixelCollision>
{
private:
public:
    //  IF PIXEL == MAGENTA -> TRUE
    bool    CheckPixel(ImageObject* ImageObj, UnitPos Pos);
    bool    CheckPixel(ImageObject * ImageObj, int x, int y);
    void    RemovePixel(ImageObject* ImageObj, UnitPos Pos);
    void    RemoveRect(ImageObject* ImageObj, RECT Rt);
    void    RemoveEllipse(ImageObject* ImageObj, RECT Rt);
};

