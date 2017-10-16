#include "stdafx.h"
#include "PhysicsHelper.h"


PhysicsHelper::PhysicsHelper()
{
}


PhysicsHelper::~PhysicsHelper()
{
}

bool PhysicsHelper::PtInsideRect(UnitPos Pos, RECT Rect)
{
    int rtWidth = Rect.right - Rect.left;
    int rtHeight = Rect.bottom - Rect.top;
    int dx = Rect.right - (int)Pos.x;
    int dy = Rect.bottom - (int)Pos.y;

    if ((dx > 0 && dx < rtWidth) &&
        (dy > 0 && dy < rtHeight))
    {
        return true;
    }
    return false;
}

UnitSpeed PhysicsHelper::CollisionAlkanoid(GameObject Unit1, GameObject Unit2)
{
    return UnitSpeed();
}