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

void Bullet::Setup()
{
}
