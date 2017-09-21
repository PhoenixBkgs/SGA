#pragma once

class Physics2DKomastar
{
public:
    Physics2DKomastar();
    ~Physics2DKomastar();

    bool PtInsideRect(UnitPos Pos, RECT Rect);

    UnitSpeed CollisionAlkanoid(UnitSpeed Speed1, UnitSpeed Speed2);
};

