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

void Enemy::Update()
{
    GameObject::Update();
    
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
