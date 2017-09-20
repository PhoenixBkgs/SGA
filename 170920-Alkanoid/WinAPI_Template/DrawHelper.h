#pragma once

inline void DrawRect(HDC hdc, RECT Rect) { Rectangle(hdc, Rect.left, Rect.top, Rect.right, Rect.bottom); }
inline void DrawEllipse(HDC hdc, RECT Rect) { Ellipse(hdc, Rect.left, Rect.top, Rect.right, Rect.bottom); }

class DrawHelper
{
public:
    DrawHelper();
    ~DrawHelper();
};

