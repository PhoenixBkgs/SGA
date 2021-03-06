#include "stdafx.h"
#include "Draw2DKomastar.h"


Draw2DKomastar::Draw2DKomastar()
{
}


Draw2DKomastar::~Draw2DKomastar()
{
}

bool Draw2DKomastar::DrawShape(E_SHAPE eShape, UnitPos Position, UnitSize Size, _RGBA Color)
{
    RECT rt;
    UnitPos LT;
    UnitPos RB;

    LT.x = Position.x - (Size.w * 0.5);
    LT.y = Position.y - (Size.h * 0.5);
    RB.x = LT.x + Size.w;
    RB.y = LT.y + Size.h;

    rt.left = (int)LT.x;
    rt.top = (int)LT.y;
    rt.right = (int)RB.x;
    rt.bottom = (int)RB.y;

    switch (eShape)
    {
    case SHAPE_RECT:
    {
        rt = MakeRect(LT, RB);
        Rectangle(g_hDC, rt.left, rt.top, rt.right, rt.bottom);
        FillRect(g_hDC, &rt, CreateSolidBrush(RGB(Color.R, Color.G, Color.B)));
        break;
    }
    case SHAPE_CIRCLE:
    {
        LT.y = Position.y - (Size.w * 0.5);
        RB.y = LT.y + Size.w;
        rt = MakeRect(LT, RB);
        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(Color.R, Color.G, Color.B));
        SelectObject(g_hDC, hPen);
        SelectObject(g_hDC, CreateSolidBrush(RGB(Color.R, Color.G, Color.B)));
        Ellipse(g_hDC, rt.left, rt.top, rt.right, rt.bottom);
        DeleteObject(hPen);
        GetStockObject(WHITE_BRUSH);
        break;
    }
    case SHAPE_ELLIPSE:
    {
        rt = MakeRect(LT, RB);
        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(Color.R, Color.G, Color.B));
        SelectObject(g_hDC, hPen);
        SelectObject(g_hDC, CreateSolidBrush(RGB(Color.R, Color.G, Color.B)));
        Ellipse(g_hDC, rt.left, rt.top, rt.right, rt.bottom);
        DeleteObject(hPen);
        GetStockObject(WHITE_BRUSH);
        break;
    }
    default:
        break;
    }

    return false;
}

bool Draw2DKomastar::DrawLine2D(UnitPos Pos1, UnitPos Pos2, int PenWidth, _RGBA Color)
{
    HPEN hPen = CreatePen(PS_SOLID, PenWidth, RGB(Color.R, Color.G, Color.B));
    SelectObject(g_hDC, hPen);
    MoveToEx(g_hDC, Pos1.x, Pos1.y, NULL);
    LineTo(g_hDC, (int)Pos2.x, (int)Pos2.y);
    DeleteObject(hPen);

    return true;
}

RECT Draw2DKomastar::MakeRect(UnitPos LT, UnitPos RB)
{
    RECT rt;
    rt.left = (int)LT.x;
    rt.top = (int)LT.y;
    rt.right = (int)RB.x;
    rt.bottom = (int)RB.y;
    return rt;
}
