#pragma once

#define _PERFECTLY_ELASTIC_COLLISION

#ifdef _PERFECTLY_ELASTIC_COLLISION             //  ����ź���浹
    #define RESTITUTION_COEF    1.0f
#elif _PERFECTLY_INELASTIC_COLLISION            //  ������ź���浹
    #define RESTITUTION_COEF    0.0f
#else
    #define RESTITUTION_COEF    0.75f           //  �浹���
#endif

class Physics2DKomastar
{
public:
    Physics2DKomastar();
    ~Physics2DKomastar();

    bool PtInsideRect(UnitPos Pos, RECT Rect);

    UnitSpeed CollisionAlkanoid(UnitSpeed Speed1, UnitSpeed Speed2);
};

