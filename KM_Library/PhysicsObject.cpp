#include "..\SGA\WinAPI_Template\WinAPI_Template\stdafx.h"
#include "PhysicsObject.h"


PhysicsObject::PhysicsObject()
{
}


PhysicsObject::~PhysicsObject()
{
}

bool PhysicsObject::PtInsideRect(UnitPos Pos, RECT Rect)
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

UnitSpeed PhysicsObject::CollisionAlkanoid(GameObject Unit1, GameObject Unit2)
{
    return UnitSpeed();
}

void PhysicsObject::MutualCollider(vector<GameObject> vecUnit1, vector<GameObject> vecUnit2)
{
    for (auto unit1CollIter = vecUnit1.begin(); unit1CollIter != vecUnit1.end(); unit1CollIter++)
    {
        for (auto unit2CollIter = vecUnit2.end(); unit2CollIter != vecUnit2.end(); unit2CollIter++)
        {
            RECT rt;
            if (IntersectRect(&rt, unit1CollIter->GetBodyRect(), unit2CollIter->GetBodyRect()))
            {
                int iter1Life = unit1CollIter->GetLifeCount();
                unit1CollIter->SumLifeCount(-unit2CollIter->GetLifeCount());
                unit2CollIter->SumLifeCount(-iter1Life);
            }
        }
    }
}

void PhysicsObject::UnitCleaner(vector<GameObject> vecUnit)
{
    for (auto eraseIter = vecUnit.begin(); eraseIter != vecUnit.end();)
    {
        if (eraseIter->GetLifeCount() <= 0)
        {
            eraseIter = vecUnit.erase(eraseIter);
        }
        else
        {
            eraseIter++;
        }
    }
}
