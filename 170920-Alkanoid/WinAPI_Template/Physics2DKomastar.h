#pragma once
#include "EnumState.h"

class Physics2DKomastar
{
public:
    Physics2DKomastar();
    ~Physics2DKomastar();

    UnitSpeed CollisionAlkanoid(UnitSpeed Speed1, UnitSpeed Speed2);
    E_REFLECT_DIR BlockCollider(RECT Ball, RECT Block);
    UnitSpeed ReflectBlock(UnitSpeed Speed, int Direction);
};

