#include "stdafx.h"
#include "ShapeDrawer.h"


ShapeDrawer::ShapeDrawer()
{
}


ShapeDrawer::~ShapeDrawer()
{
}

void ShapeDrawer::DrawRectangle(HDC hdc, RECT rect)
{
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}
