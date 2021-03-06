#include "stdafx.h"
#include "Draw2DKomastar.h"


Draw2DKomastar::Draw2DKomastar()
{
}


Draw2DKomastar::~Draw2DKomastar()
{
}

bool Draw2DKomastar::DrawShape(E_SHAPE eShape, UnitPos Position, UnitSize Size, HBRUSH* Brush)
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
        FillRect(g_hDC, &rt, *Brush);
        break;
    }
    }

    return false;
}

bool Draw2DKomastar::DrawLine2D(UnitPos Pos1, UnitPos Pos2, int PenWidth, _RGBA Color)
{
    HPEN hPen = CreatePen(PS_SOLID, PenWidth, RGB(Color.R, Color.G, Color.B));
    SelectObject(g_hDC, hPen);
    MoveToEx(g_hDC, (int)Pos1.x, (int)Pos1.y, NULL);
    LineTo(g_hDC, (int)Pos2.x, (int)Pos2.y);
    DeleteObject(hPen);

    return true;
}

void Draw2DKomastar::DrawBoxLine2D(RECT rt, int LineWidth, _RGBA Color)
{
    UnitPos lt = { (double)rt.left, (double)rt.top };
    UnitPos rb = { (double)rt.right, (double)rt.bottom };

    DrawLine2D(lt, UnitPos{ rb.x, lt.y }, LineWidth, Color);
    DrawLine2D(lt, UnitPos{ lt.x, rb.y }, LineWidth, Color);
    DrawLine2D(rb, UnitPos{ rb.x, lt.y }, LineWidth, Color);
    DrawLine2D(rb, UnitPos{ lt.x, rb.y }, LineWidth, Color);
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

void Draw2DKomastar::DrawCenterText(string TextString, int FontSize, _RGBA FontColor, string FontName)
{
    PatBlt(g_hDC, 0, (int)(W_HEIGHT * 0.33), W_WIDTH, (int)(W_HEIGHT * 0.33), BLACKNESS);

    RECT rt = { 0, 0, W_WIDTH, W_HEIGHT };
    HFONT hFont, hTmp;
    SetTextColor(g_hDC, RGB(FontColor.R, FontColor.G, FontColor.B));
    hFont = CreateFont(FontSize, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 2, 0, FontName.data());
    hTmp = (HFONT)SelectObject(g_hDC, hFont);
    SetBkMode(g_hDC, TRANSPARENT);
    DrawText(g_hDC, TextString.data(), -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    DeleteObject(SelectObject(g_hDC, hTmp));
}

void Draw2DKomastar::DrawTextBox(RECT TxtBox, string TextString, _RGBA FontColor, string FontName)
{
    HFONT hFont, hTmp;
    int FontSize = TxtBox.bottom - TxtBox.top;
    SetTextColor(g_hDC, RGB(FontColor.R, FontColor.G, FontColor.B));
    hFont = CreateFont(FontSize, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 2, 0, FontName.data());
    hTmp = (HFONT)SelectObject(g_hDC, hFont);
    SetBkMode(g_hDC, TRANSPARENT);
    DrawText(g_hDC, TextString.data(), -1, &TxtBox, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    DeleteObject(SelectObject(g_hDC, hTmp));
}