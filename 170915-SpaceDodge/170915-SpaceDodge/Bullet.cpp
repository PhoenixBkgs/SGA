#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
    Setup();
}


Bullet::~Bullet()
{
}

void Bullet::Setup()
{
    m_moveSpeed.push_back(1);
    m_moveSpeed.push_back(1);
}

void Bullet::Update()
{
    m_bulletRect.left += m_moveSpeed[0];
    m_bulletRect.right += m_moveSpeed[0];
    m_bulletRect.top += m_moveSpeed[1];
    m_bulletRect.bottom += m_moveSpeed[1];
}

void Bullet::Render(HDC hdc)
{
    Rectangle(hdc, m_bulletRect.left, m_bulletRect.top, m_bulletRect.right, m_bulletRect.bottom);
}
