#include "stdafx.h"
#include "GameUnit.h"


GameUnit::GameUnit()
{
}

GameUnit::GameUnit(POINT Position, HBRUSH Brush)
{
    SetBodyRect(Position, POINT{1, 1});
    m_bBrush = Brush;
}

GameUnit::GameUnit(POINT Position, POINT Size, HBRUSH Brush, int Life)
{
    SetBodyRect(Position, Size);
    SetLifeCount(Life);
    m_bBrush = Brush;
}


GameUnit::~GameUnit()
{
}

void GameUnit::SetBodyRect(POINT GenPos)
{
    POINT LT;
    POINT RB;
    LT.x = GenPos.x;
    LT.y = GenPos.y;
    RB.x = GenPos.x + 2;
    RB.y = GenPos.y + 2;

    m_rtBody = { LT.x, LT.y, RB.x, RB.y };
}

void GameUnit::SetBodyRect(POINT GenPos, POINT BodySize)
{
    POINT LT;
    POINT RB;
    int halfWidth = (int)(BodySize.x * 0.5);
    int halfHeight = (int)(BodySize.y * 0.5);
    LT.x = GenPos.x - halfWidth;
    LT.y = GenPos.y - halfHeight;
    RB.x = GenPos.x + halfWidth;
    RB.y = GenPos.y + halfHeight;

    m_rtBody = { LT.x, LT.y, RB.x, RB.y };
}

void GameUnit::SetColor(int R, int G, int B)
{
    m_bBrush = CreateSolidBrush(RGB(R, G, B));
}

void GameUnit::Move()
{
    m_rtBody.left += m_ptMoveDir.x;
    m_rtBody.right += m_ptMoveDir.x;
    m_rtBody.top += m_ptMoveDir.y;
    m_rtBody.bottom += m_ptMoveDir.y;
}

void GameUnit::Draw(bool DrawForce)
{
    if (DrawForce)
    {
        DrawRect(g_hDC, m_rtBody);
    }
    else
    {
        if (m_LifeCount > 0)
        {
            DrawRect(g_hDC, m_rtBody);
        }
    }
}

void GameUnit::Destroy()
{
    m_LifeCount = 0;
}

bool GameUnit::Collider(RECT * TargetRect)
{
    RECT rt;
    if (IntersectRect(&rt, TargetRect, &m_rtBody))
    {
        //  COLLISION DETECTED !
        return true;
    }
    //  NO COLLISION !
    return false;
}
