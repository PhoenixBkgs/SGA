#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

E_EDGE Enemy::IsInsideWindow(bool AllStop)
{
    if (m_map.IsRectOutside(&m_rtBody, 0))
    {
        //  END OF LEFT
        return LEFT_EDGE;
    }
    else if (m_map.IsRectOutside(&m_rtBody, 1))
    {
        //  END OF RIGHT
        return RIGHT_EDGE;
    }
    else if (m_map.IsEnemyArrive(&m_rtBody))
    {
        return BOTTOM_EDGE;
    }

    return END_EDGE;
}
