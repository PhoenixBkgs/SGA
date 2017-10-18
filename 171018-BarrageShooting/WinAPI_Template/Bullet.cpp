#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}

Bullet::Bullet(string szTagName)
{
    m_szTagName = szTagName;
    SetBodyImgAuto();
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
        SetLife(0);
    }
    if (pos.x > W_WIDTH)
    {
        SetLife(0);
    }
    if (pos.y < 0)
    {
        SetLife(0);
    }
    if (pos.y > W_HEIGHT)
    {
        SetLife(0);
    }
}
