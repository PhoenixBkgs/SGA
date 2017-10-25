#include "stdafx.h"
#include "PixelCollision.h"


bool PixelCollision::CheckPixel(ImageObject * ImageObj, UnitPos Pos)
{
    COLORREF color = GetPixel(ImageObj->GetMemDC(), Pos.x, Pos.y);
    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);

    if (r == 255 &&
        g == 0 &&
        b == 255)
    {
        return true;
    }

    return false;
}

void PixelCollision::RemovePixel(ImageObject* ImageObj, UnitPos Pos)
{
    SetPixel(ImageObj->GetMemDC(), (int)Pos.x, (int)Pos.y, RGB(255, 0, 255));
}

void PixelCollision::RemoveRect(ImageObject * ImageObj, RECT Rt)
{
    HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(ImageObj->GetMemDC(), hBrush);
    HPEN hPen = (HPEN)CreatePen(0, 1, RGB(255, 0, 255));
    HPEN hOldPen = (HPEN)SelectObject(ImageObj->GetMemDC(), hPen);

    Rectangle(ImageObj->GetMemDC(), Rt.left, Rt.top, Rt.right, Rt.bottom);

    DeleteObject(hOldPen);
    DeleteObject(hPen);
    DeleteObject(hOldBrush);
    DeleteObject(hBrush);
}

void PixelCollision::RemoveEllipse(ImageObject * ImageObj, RECT Rt)
{
    HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(ImageObj->GetMemDC(), hBrush);
    HPEN hPen = (HPEN)CreatePen(0, 1, RGB(255, 0, 255));
    HPEN hOldPen = (HPEN)SelectObject(ImageObj->GetMemDC(), hPen);

    Ellipse(ImageObj->GetMemDC(), Rt.left, Rt.top, Rt.right, Rt.bottom);

    DeleteObject(hOldPen);
    DeleteObject(hPen);
    DeleteObject(hOldBrush);
    DeleteObject(hBrush);
}
