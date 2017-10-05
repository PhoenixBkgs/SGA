#include "stdafx.h"
#include "Physics2DKomastar.h"


Physics2DKomastar::Physics2DKomastar()
{
}


Physics2DKomastar::~Physics2DKomastar()
{
}

UnitSpeed Physics2DKomastar::CollisionAlkanoid(GameUnit Unit1, GameUnit Unit2)
{
    return UnitSpeed();
}

void Physics2DKomastar::MutualCollider(vector<GameUnit> vecUnit1, vector<GameUnit> vecUnit2)
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

void Physics2DKomastar::UnitCleaner(vector<GameUnit> vecUnit)
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
