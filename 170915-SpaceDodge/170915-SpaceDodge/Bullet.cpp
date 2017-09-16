#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(Player player)
{
    Setup(player);
}


Bullet::~Bullet()
{
}

void Bullet::Setup(Player player)
{
    bool m_isInside = false;
    E_GEN_DIRECTION eGenDirection = (E_GEN_DIRECTION)(rand() % 4);
    srand(time(NULL));
    int bulletPosX = rand() % WIN_WIDTH;
    int bulletPosY = rand() % WIN_HEIGHT;

    switch (eGenDirection)
    {
    case TOP:
        bulletPosY -= WIN_HEIGHT;
        break;
    case LEFT:
        bulletPosX -= WIN_WIDTH;
        break;
    case RIGHT:
        bulletPosX += WIN_WIDTH;
        break;
    case DOWN:
        bulletPosY += WIN_HEIGHT;
        break;
    default:
        break;
    }

    m_bulletRect.left = bulletPosX - BULLET_H_SIZE;
    m_bulletRect.right = bulletPosX + BULLET_H_SIZE;
    m_bulletRect.top = bulletPosY - BULLET_H_SIZE;
    m_bulletRect.bottom = bulletPosY + BULLET_H_SIZE;

    POINT ptPlayer;
    POINT ptBulletPos;
    vector<double> vecDirection;
    MathVectorCalc vCalc;
    ptPlayer = player.GetPlayerPos();
    ptBulletPos.x = bulletPosX;
    ptBulletPos.y = bulletPosY;
    vecDirection = vCalc.GetDirection(ptPlayer, ptBulletPos, 0.01f);

    m_moveSpeed.push_back(vecDirection[0]);
    m_moveSpeed.push_back(vecDirection[1]);
}

void Bullet::Update()
{
    m_bulletPosX += m_moveSpeed[0];
    m_bulletPosY += m_moveSpeed[1];

    m_bulletRect.left = (LONG)(m_bulletPosX - BULLET_H_SIZE);
    m_bulletRect.right = (LONG)(m_bulletPosX + BULLET_H_SIZE);
    m_bulletRect.top = (LONG)(m_bulletPosY - BULLET_H_SIZE);
    m_bulletRect.bottom = (LONG)(m_bulletPosY + BULLET_H_SIZE);
}

void Bullet::Render(HDC hdc)
{
    DrawRectangle(hdc, m_bulletRect);
}
