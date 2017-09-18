#pragma once
class ShapeDrawer
{
public:
    ShapeDrawer();
    ~ShapeDrawer();
    
    void DrawRectangle(HDC hdc, RECT rect, HBRUSH brush);
};

