#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}

Bullet::Bullet(string szTagName)
{
    m_szTagName = szTagName;
    SetBodyImgAuto();
    m_dDmg = -1.0f;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
    SpritesObject::Update();
    SetFrameX(0);
    /*
    UnitPos tPos;
    UnitPos pos = g_pGeoHelper->GetCenterPointWindow();
    m_t += 0.01f;
    g_pGeoHelper->BezierInterpolation(tPos, GetPos(), pos, UnitPos{ (double)W_WIDTH, (double)W_HEIGHT }, m_t);
    SetBodyPos(tPos);
    m_rtBody = g_pDrawHelper->MakeRect(m_dPos, GetSize());
    */
    UnitPos pos = GetPos();
    if (pos.x < 0)
    {
        SetDead();
    }
    if (pos.x > W_WIDTH)
    {
        SetDead();
    }
    if (pos.y < 0)
    {
        SetDead();
    }
    if (pos.y > W_HEIGHT)
    {
        SetDead();
    }
}
