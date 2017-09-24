#include "stdafx.h"
#include "DrawHelper.h"


DrawHelper::DrawHelper()
{
}


DrawHelper::~DrawHelper()
{
}


bool DrawHelper::DrawLine2D(UnitPos Pos1, UnitPos Pos2, int PenWidth, RGBA Color)
{
    HPEN hPen = CreatePen(PS_SOLID, PenWidth, RGB(Color.R, Color.G, Color.B));
    SelectObject(g_hDC, hPen);
    MoveToEx(g_hDC, Pos1.x, Pos1.y, NULL);
    LineTo(g_hDC, Pos2.x, Pos2.y);
    DeleteObject(hPen);

    return true;
}
