#include "stdafx.h"
#include "GameUnit.h"


GameUnit::GameUnit()
{
}

GameUnit::GameUnit(UnitPos Position, HBRUSH* Brush)  //  2x2
{
    SetBodyRect(Position, UnitSize{2, 2});
    m_bBrush = Brush;
}

GameUnit::GameUnit(UnitPos Position, UnitSize Size, HBRUSH* Brush, int Life) //  custom size
{
    SetBodyRect(Position, Size);
    SetLifeCount(Life);
    m_bBrush = Brush;
}


GameUnit::~GameUnit()
{
}

void GameUnit::SetBodyRect(UnitPos GenPos, UnitSize BodySize)
{
    int halfWidth = (int)(BodySize.w * 0.5);
    int halfHeight = (int)(BodySize.h * 0.5);
    
    m_rtBody.left =     (int)GenPos.x - halfWidth;
    m_rtBody.top =      (int)GenPos.y - halfHeight;
    m_rtBody.right =    m_rtBody.left + BodySize.w;
    m_rtBody.bottom =   m_rtBody.top + BodySize.h;
}

void GameUnit::SetColor(int R, int G, int B)
{
    *m_bBrush = CreateSolidBrush(RGB(R, G, B));
}

void GameUnit::UpdateBodyPos(UnitPos GenPos)
{
    m_rtBody.left =     (int)(GenPos.x - (m_unitSize.w * 0.5));
    m_rtBody.top =      (int)(GenPos.y - (m_unitSize.w * 0.5));
    m_rtBody.right =    m_rtBody.left + m_unitSize.w;
    m_rtBody.bottom =   m_rtBody.top + m_unitSize.h;
}

void GameUnit::Move()
{
    m_unitPos.x += m_moveSpeed.x;
    m_unitPos.y += m_moveSpeed.y;
    UpdateBodyPos(m_unitPos);
}

void GameUnit::Destroy()
{
    m_LifeCount = 0;
}