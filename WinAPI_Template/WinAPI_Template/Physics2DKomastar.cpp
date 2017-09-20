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
