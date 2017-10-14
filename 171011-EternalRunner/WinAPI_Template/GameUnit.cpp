#include "stdafx.h"
#include "GameUnit.h"


GameUnit::GameUnit()
{
    m_isMovable = true;
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

RECT GameUnit::SetBodyRect(UnitPos GenPos, UnitSize BodySize, int Margin)
{
    RECT tRetRect;
    BodySize.w -= Margin;
    BodySize.h -= Margin;
    int halfWidth = (int)((BodySize.w) * 0.5);
    int halfHeight = (int)((BodySize.h) * 0.5);

    tRetRect.left = (int)GenPos.x - halfWidth;
    tRetRect.top = (int)GenPos.y - halfHeight;
    tRetRect.right = tRetRect.left + BodySize.w;
    tRetRect.bottom = tRetRect.top + BodySize.h;

    return tRetRect;
}

void GameUnit::RenderBodyRect(HDC hdc)
{
#ifdef _DEBUG
    char infoMsg[100];
    sprintf_s(infoMsg, "X : %f / Y : %f", m_unitPos.x, m_unitPos.y);
    Rectangle(hdc, m_rtBody.left, m_rtBody.top - 20, m_rtBody.right, m_rtBody.top);
    TextOut(g_hDC, m_rtBody.left, m_rtBody.top - 20, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
    Rectangle(hdc, m_rtBody.left, m_rtBody.top, m_rtBody.right, m_rtBody.bottom);
}

void GameUnit::SetColor(int R, int G, int B)
{
    *m_bBrush = CreateSolidBrush(RGB(R, G, B));
}

void GameUnit::UpdateBodyPos(UnitPos GenPos)
{
    m_rtBody.left =     (int)(GenPos.x - (m_unitSize.w * 0.5));
    m_rtBody.top =      (int)(GenPos.y - (m_unitSize.h * 0.5));
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

void GameUnit::BoxCollider2D(vector<GameUnit> MultipleUnit)
{
    for (auto iter = MultipleUnit.begin(); iter != MultipleUnit.end(); iter++)
    {
        RECT rt;
        if (IntersectRect(&rt, &m_rtBody, iter->GetBodyRect()))
        {
            if (m_isImmortal == false)
            {
                m_LifeCount -= 1;
            }
            
            if (iter->m_isImmortal == false)
            {
                iter->m_LifeCount -= 1;
            }
        }
    }
}
