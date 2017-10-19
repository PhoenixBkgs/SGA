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
