#pragma once
#include "EnumState.h"

class DrawHelper
{
public:
    DrawHelper();
    ~DrawHelper();

    bool DrawShape(E_SHAPE eShape, UnitPos Position, UnitSize Size, HBRUSH* Brush);
    bool DrawLine2D(UnitPos Pos1, UnitPos Pos2, int PenWidth, _RGBA Color);
    void DrawBoxLine2D(RECT rt, int LineWidth, _RGBA Color);
    RECT MakeRect(UnitPos LT, UnitPos RB);

    void DrawCenterText(string TextString, int FontSize, _RGBA FontColor = { 0, 0, 0, 0 }, string FontName = "SYSTEM_FIXED_FONT");
    void DrawTextBox(RECT TxtBox, string TextString, _RGBA FontColor = { 0, 0, 0, 0 }, string FontName = "SYSTEM_FIXED_FONT");
};