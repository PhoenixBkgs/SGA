#pragma once
#include "GameUnit.h"

#define _PERFECTLY_ELASTIC_COLLISION

#ifdef _PERFECTLY_ELASTIC_COLLISION             //  완전탄성충돌
    #define RESTITUTION_COEF    1.0f
#elif _PERFECTLY_INELASTIC_COLLISION            //  완전비탄성충돌
    #define RESTITUTION_COEF    0.0f
#else
    #define RESTITUTION_COEF    0.75f           //  충돌계수
#endif

class Physics2DKomastar
{
public:
    Physics2DKomastar();
    ~Physics2DKomastar();

    UnitSpeed CollisionAlkanoid(GameUnit Unit1, GameUnit Unit2);
    void MutualCollider(vector<GameUnit> vecUnit1, vector<GameUnit> vecUnit2);
    void UnitCleaner(vector<GameUnit> vecUnit);
};