#include "stdafx.h"
#include "GameUnit.h"


GameUnit::GameUnit()
{
}

GameUnit::GameUnit(POINT Position, HBRUSH Brush)
{
    m_isRender = true;
    SetBodyRect(Position, POINT{1, 1});
    m_bBrush = Brush;
    m_ptPos = Position;
}

GameUnit::GameUnit(POINT Position, POINT Size, HBRUSH Brush, int Life)
{
    m_isRender = true;
    SetBodyRect(Position, Size);
    SetLifeCount(Life);
    m_bBrush = Brush;
    m_ptPos = Position;
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

void GameUnit::SetPosition(POINT Pos)
{
    m_rtBody.left   += Pos.x;
    m_rtBody.right  += Pos.x;
    m_rtBody.top    += Pos.y;
    m_rtBody.bottom += Pos.y;
    m_ptPos.x += Pos.x;
    m_ptPos.y += Pos.y;
}

void GameUnit::SetMoveDirReverse(E_REFLECT_DIR Dir)
{
    switch (Dir)
    {
    case REVERSE_ALL:
        m_ptMoveDir.x = -m_ptMoveDir.x;
        m_ptMoveDir.y = -m_ptMoveDir.y;
        break;
    case REVERSE_X:
        m_ptMoveDir.x = -m_ptMoveDir.x;
        break;
    case REVERSE_Y:
        m_ptMoveDir.y = -m_ptMoveDir.y;
        break;
    }
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

void GameUnit::Stop()
{
    m_ptMoveDir = UnitSpeed{ 0.0f, 0.0f };
}

void GameUnit::Draw(E_SHAPE Shape, bool DrawForce)
{
    if (m_isRender == false)
    {
        return;
    }

    switch (Shape)
    {
    case SHAPE_RECT:
        DrawRect(g_hDC, m_rtBody);
        break;
    case SHAPE_ELLIPSE:
        DrawEllipse(g_hDC, m_rtBody);
        break;
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
