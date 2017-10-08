#pragma once
#include "EnumState.h"

class Draw2DKomastar
{
public:
    Draw2DKomastar();
    ~Draw2DKomastar();

    bool DrawShape(E_SHAPE eShape, UnitPos Position, UnitSize Size, HBRUSH* Brush);
    bool DrawLine2D(UnitPos Pos1, UnitPos Pos2, int PenWidth, _RGBA Color);

    RECT MakeRect(UnitPos LT, UnitPos RB);

    void DrawCenterText(string TextString, int FontSize, int PosY, _RGBA FontColor = { 0, 0, 0, 0 }, string FontName = "SYSTEM_FIXED_FONT");
};