#pragma once

inline void DrawRect(HDC hdc, RECT Rect) { Rectangle(hdc, Rect.left, Rect.top, Rect.right, Rect.bottom); }

class DrawHelper
{
public:
    DrawHelper();
    ~DrawHelper();
};

