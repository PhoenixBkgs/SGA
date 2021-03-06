#include "stdafx.h"
#include "PhysicsHelper.h"

template<class T>
bool PhysicsHelper::IsCollision(T Unit1, T Unit2)
{
    RECT tempRt;
    return IntersectRect(&tempRt, &Unit1.GetBodyRect(), &Unit2.GetBodyRect()) ? true : false;
}

template<class T>
void PhysicsHelper::BoxCollider(T VecUnit1, vector<T> VecUnit2, int DmgDeal1, int DmgDeal2)
{
    for (auto iter2 = VecUnit2.begin(); iter2 != VecUnit2.end(); iter2++)
    {
        if (IsCollision(VecUnit1, *iter2))
        {
            iter->SumLife(DmgDeal1);
            iter2->SumLife(DmgDeal2);
        }
    }
}

template<class T>
void PhysicsHelper::BoxCollider(vector<T> VecUnit1, vector<T> VecUnit2, int DmgDeal1, int DmgDeal2)
{
    for (auto iter = VecUnit1.begin(); iter != VecUnit1.end(); iter++)
    {
        for (auto iter2 = VecUnit2.begin(); iter2 != VecUnit2.end(); iter2++)
        {
            if (IsCollision(*iter, *iter2))
            {
                iter->SumLife(DmgDeal1);
                iter2->SumLife(DmgDeal2);
            }
        }
    }
}