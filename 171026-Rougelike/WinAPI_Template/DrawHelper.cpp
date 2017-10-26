#include "stdafx.h"
#include "DrawHelper.h"

DrawHelper::DrawHelper()
{
    m_pBrushRed = new HBRUSH;
    m_pBrushGreen = new HBRUSH;
    m_pBrushBlue = new HBRUSH;

    *m_pBrushRed = CreateSolidBrush(RGB(255, 0, 0));
    *m_pBrushGreen = CreateSolidBrush(RGB(0, 255, 0));
    *m_pBrushBlue = CreateSolidBrush(RGB(0, 0, 255));
}

DrawHelper::~DrawHelper()
{
    SAFE_DELETE(m_pBrushRed);
    SAFE_DELETE(m_pBrushGreen);
    SAFE_DELETE(m_pBrushBlue);
}

bool DrawHelper::DrawLine2D(UnitPos Pos1, UnitPos Pos2, int PenWidth, int ColorCode)
{
    HPEN* hPen = new HPEN; 
    switch (ColorCode)
    {
    case 1:
        *hPen = CreatePen(PS_SOLID, PenWidth, RGB(255, 0, 0));
        break;
    case 2:
        *hPen = CreatePen(PS_SOLID, PenWidth, RGB(0, 255, 0));
        break;
    case 3:
        *hPen = CreatePen(PS_SOLID, PenWidth, RGB(0, 0, 255));
        break;
    default:
        *hPen = CreatePen(PS_SOLID, PenWidth, RGB(0, 0, 0));
        break;
    }
    SelectObject(g_hDC, *hPen);
    MoveToEx(g_hDC, (int)Pos1.x, (int)Pos1.y, NULL);
    LineTo(g_hDC, (int)Pos2.x, (int)Pos2.y);
    DeleteObject(*hPen);
    SAFE_DELETE(hPen);

    return true;
}

void DrawHelper::DrawBoxLine2D(RECT rt, int LineWidth, int ColorCode)
{
    UnitPos lt = { (double)rt.left, (double)rt.top };
    UnitPos rb = { (double)rt.right, (double)rt.bottom };

    DrawLine2D(lt, UnitPos{ rb.x, lt.y }, LineWidth, ColorCode);
    DrawLine2D(lt, UnitPos{ lt.x, rb.y }, LineWidth, ColorCode);
    DrawLine2D(rb, UnitPos{ rb.x, lt.y }, LineWidth, ColorCode);
    DrawLine2D(rb, UnitPos{ lt.x, rb.y }, LineWidth, ColorCode);
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
        SAFE_DELETE(pBrush);
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
