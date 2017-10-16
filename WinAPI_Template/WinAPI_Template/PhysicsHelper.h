#pragma once
#include "GameObject.h"

#define _PERFECTLY_ELASTIC_COLLISION

#ifdef _PERFECTLY_ELASTIC_COLLISION             //  완전탄성충돌
    #define RESTITUTION_COEF    1.0f
#elif _PERFECTLY_INELASTIC_COLLISION            //  완전비탄성충돌
    #define RESTITUTION_COEF    0.0f
#else
    #define RESTITUTION_COEF    0.75f           //  충돌계수
#endif

class PhysicsHelper
{
public:
    PhysicsHelper();
    ~PhysicsHelper();

    bool PtInsideRect(UnitPos Pos, RECT Rect);
    UnitSpeed CollisionAlkanoid(GameObject Unit1, GameObject Unit2);
    void MutualCollider(vector<GameObject> vecUnit1, vector<GameObject> vecUnit2);
    void UnitCleaner(vector<GameObject> vecUnit);
};