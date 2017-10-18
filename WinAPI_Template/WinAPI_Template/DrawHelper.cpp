#include "stdafx.h"
#include "DrawHelper.h"

bool DrawHelper::DrawLine2D(UnitPos Pos1, UnitPos Pos2, int PenWidth, _RGBA Color)
{
    HPEN hPen = CreatePen(PS_SOLID, PenWidth, RGB(Color.R, Color.G, Color.B));
    SelectObject(g_hDC, hPen);
    MoveToEx(g_hDC, (int)Pos1.x, (int)Pos1.y, NULL);
    LineTo(g_hDC, (int)Pos2.x, (int)Pos2.y);
    DeleteObject(hPen);

    return true;
}

void DrawHelper::DrawBoxLine2D(RECT rt, int LineWidth, _RGBA Color)
{
    UnitPos lt = { (double)rt.left, (double)rt.top };
    UnitPos rb = { (double)rt.right, (double)rt.bottom };

    DrawLine2D(lt, UnitPos{ rb.x, lt.y }, LineWidth, Color);
    DrawLine2D(lt, UnitPos{ lt.x, rb.y }, LineWidth, Color);
    DrawLine2D(rb, UnitPos{ rb.x, lt.y }, LineWidth, Color);
    DrawLine2D(rb, UnitPos{ lt.x, rb.y }, LineWidth, Color);
}

RECT DrawHelper::MakeRect(UnitPos Pos, UnitSize Size)
{
    RECT rt;
    rt.left = (int)(Pos.x - Size.w * 0.5f);
    rt.top  = (int)(Pos.y - Size.h * 0.5f);
    rt.right = rt.left + Size.w;
    rt.bottom = rt.top + Size.h;

    return rt;
}

void DrawHelper::DrawTextBox(HDC hdc, RECT TxtBox, string TextString)
{
    HFONT hFont, hTmp;
    int FontSize = TxtBox.bottom - TxtBox.top;
    SetTextColor(g_hDC, RGB(m_textBoxInfo.FontColor.R
                            , m_textBoxInfo.FontColor.G
                            , m_textBoxInfo.FontColor.B));
    hFont = CreateFont(FontSize, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 2, 0, m_textBoxInfo.FontName.data());
    hTmp = (HFONT)SelectObject(g_hDC, hFont);
    SetBkMode(g_hDC, TRANSPARENT);
    if (m_textBoxInfo.IsVisibleBox)
    {
        HBRUSH* pBrush = new HBRUSH;
        *pBrush = CreateSolidBrush(RGB(m_textBoxInfo.BoxColor.R, m_textBoxInfo.BoxColor.G, m_textBoxInfo.BoxColor.B));
        FillRect(hdc, &TxtBox, *pBrush);
        delete pBrush;
    }
    DrawText(g_hDC, TextString.data(), -1, &TxtBox, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    DeleteObject(SelectObject(g_hDC, hTmp));
}

UnitSize DrawHelper::GetSizeFromRect(RECT Rect)
{
    return UnitSize{ Rect.right - Rect.left, Rect.bottom - Rect.top };
}

UnitPos DrawHelper::GetPosFromRect(RECT Rect)
{
    UnitSize nSize = GetSizeFromRect(Rect);
    return UnitPos{ (double)(Rect.left + (nSize.w * 0.5f))
                  , (double)(Rect.top  + (nSize.h * 0.5f)) };
}
