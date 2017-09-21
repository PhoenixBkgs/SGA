#pragma once
#include "EnumState.h"

class Draw2DKomastar
{
public:
    Draw2DKomastar();
    ~Draw2DKomastar();

    bool DrawShape(E_SHAPE eShape, UnitPos Position, UnitSize Size, HBRUSH Brush);

    RECT DrawRect(UnitPos Position, UnitSize Size, HBRUSH Brush);
    RECT DrawCircle(UnitPos Position, UnitSize Size, RGBA Color);
    RECT DrawEllipse(UnitPos Position, UnitSize Size, RGBA Color);
};