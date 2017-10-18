#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}

Enemy::Enemy(string szTagName)
{
    m_szTagName = szTagName;
    SetBodyImgAuto();
}


Enemy::~Enemy()
{
}

void Enemy::PushBullet(Bullet Bullet)
{
    m_vecBullets.push_back(Bullet);
}

void Enemy::Update()
{
    SpritesObject::Update();
    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
    {
        iter->Update();
    }
}

void Enemy::Render()
{
    SpritesObject::Render();
    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
    {
        iter->Render();
    }
}


void Enemy::PatternA()
{
}

void Enemy::PatternB()
{
}

void Enemy::PatternC()
{
}
