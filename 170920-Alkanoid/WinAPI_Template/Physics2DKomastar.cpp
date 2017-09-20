#include "stdafx.h"
#include "Physics2DKomastar.h"


Physics2DKomastar::Physics2DKomastar()
{
}


Physics2DKomastar::~Physics2DKomastar()
{
}

UnitSpeed Physics2DKomastar::CollisionAlkanoid(UnitSpeed Speed1, UnitSpeed Speed2)
{
    UnitSpeed retUnitSpeed = Speed2;
    retUnitSpeed.x = Speed2.x - Speed1.x;

    return retUnitSpeed;
}

E_REFLECT_DIR Physics2DKomastar::BlockCollider(RECT Ball, RECT Block)
{
    E_REFLECT_DIR retDirection = REVERSE_END;
    RECT rt;
    RECT BallRt = Ball;
    RECT BlockRt = Block;
    if (IntersectRect(&rt, &BallRt, &BlockRt))
    {
        int rtWidth = rt.right - rt.left;
        int rtHeight = rt.bottom - rt.top;

        if (rtWidth < rtHeight)
        {
            retDirection = REVERSE_X;
        }
        else if (rtWidth > rtHeight)
        {
            retDirection = REVERSE_Y;
        }
        if (rtWidth == rtHeight)
        {
            retDirection = REVERSE_ALL;
        }
    }
    return retDirection;
}

UnitSpeed Physics2DKomastar::ReflectBlock(UnitSpeed Speed, int Direction)
{
    if (Direction == 0)
    {
        //  횡이동
        Speed.y = -Speed.y;
    }
    else
    {
        //  종이동
        Speed.x = -Speed.x;
    }

    return Speed;
}
