#include "stdafx.h"
#include "ShapeDrawer.h"


ShapeDrawer::ShapeDrawer()
{
}


ShapeDrawer::~ShapeDrawer()
{
}

void ShapeDrawer::DrawRectangle(HDC hdc, RECT rect, HBRUSH brush)
{
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    FillRect(hdc, &rect, brush);
}
