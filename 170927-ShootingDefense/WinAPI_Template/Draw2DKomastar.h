#pragma once
#include "EnumState.h"

class Draw2DKomastar
{
public:
    Draw2DKomastar();
    ~Draw2DKomastar();

    bool DrawShape(E_SHAPE eShape, UnitPos Position, UnitSize Size, _RGBA Color);
    bool DrawLine2D(UnitPos Pos1, UnitPos Pos2, int PenWidth, _RGBA Color);

    RECT MakeRect(UnitPos LT, UnitPos RB);
};