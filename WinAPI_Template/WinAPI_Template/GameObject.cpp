#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
    m_isMovable = true;
}

GameObject::GameObject(UnitPos Position, HBRUSH Brush)  //  2x2
{
    SetBodyRect(Position, UnitSize{2, 2});
    m_bBrush = Brush;
}

GameObject::GameObject(UnitPos Position, UnitSize Size, HBRUSH Brush, int Life) //  custom size
{
    SetBodyRect(Position, Size);
    SetLifeCount(Life);
    m_bBrush = Brush;
}


GameObject::~GameObject()
{
}

void GameObject::SetBodyRect(UnitPos GenPos, UnitSize BodySize)
{
    int halfWidth = (int)(BodySize.w * 0.5);
    int halfHeight = (int)(BodySize.h * 0.5);
    
    m_rtBody.left =     (int)GenPos.x - halfWidth;
    m_rtBody.top =      (int)GenPos.y - halfHeight;
    m_rtBody.right =    m_rtBody.left + BodySize.w;
    m_rtBody.bottom =   m_rtBody.top + BodySize.h;
}

RECT GameObject::SetBodyRect(UnitPos GenPos, UnitSize BodySize, int Margin)
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

void GameObject::SetColor(int R, int G, int B)
{
    m_bBrush = CreateSolidBrush(RGB(R, G, B));
}

void GameObject::UpdateBodyPos(UnitPos GenPos)
{
    m_rtBody.left =     (int)(GenPos.x - (m_unitSize.w * 0.5));
    m_rtBody.top =      (int)(GenPos.y - (m_unitSize.w * 0.5));
    m_rtBody.right =    m_rtBody.left + m_unitSize.w;
    m_rtBody.bottom =   m_rtBody.top + m_unitSize.h;
}

void GameObject::Move()
{
    m_unitPos.x += m_moveSpeed.x;
    m_unitPos.y += m_moveSpeed.y;
    UpdateBodyPos(m_unitPos);
}

void GameObject::Destroy()
{
    m_LifeCount = 0;
}

void GameObject::BoxCollider2D(vector<GameObject> MultipleUnit)
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
