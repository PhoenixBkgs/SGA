#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}

Bullet::Bullet(UnitPos GenPos)
{
    m_unitSize.w = BULLET_SIZE;
    m_unitSize.h = BULLET_SIZE;

    SetBodyRect(GenPos, m_unitSize);
    m_unitPos = GenPos;
    m_LifeCount = 1;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
    Move();
}

void Bullet::Render()
{
    //m_drawHelper.DrawShape(SHAPE_RECT, m_unitPos, m_unitSize, _RGBA{ 0, 0, 0, 0 });
    Rectangle(g_hDC, m_rtBody.left, m_rtBody.top, m_rtBody.right, m_rtBody.bottom);
    FillRect(g_hDC, &m_rtBody, *m_bBrush);
}
