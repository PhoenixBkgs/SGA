#include "stdafx.h"
#include "Physics2DKomastar.h"


Physics2DKomastar::Physics2DKomastar()
{
}


Physics2DKomastar::~Physics2DKomastar()
{
}

bool Physics2DKomastar::PtInsideRect(UnitPos Pos, RECT Rect)
{
    int rtWidth = Rect.right - Rect.left;
    int rtHeight = Rect.bottom - Rect.top;
    int dx = Rect.right - (int)Pos.x;
    int dy = Rect.bottom - (int)Pos.y;

    if ((dx >= 0 && dx <= rtWidth) &&
        (dy >= 0 && dy <= rtHeight))
    {
        return true;
    }
    return false;
}

UnitSpeed Physics2DKomastar::CollisionAlkanoid(UnitSpeed Speed1, UnitSpeed Speed2)
{
    UnitSpeed retUnitSpeed = Speed2;
    retUnitSpeed.x = Speed2.x - Speed1.x;

    return retUnitSpeed;
}
