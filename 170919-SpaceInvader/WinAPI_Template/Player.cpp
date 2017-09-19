#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::IsInsideWindow(bool IsStop)
{
    if (m_map.IsRectOutside(&m_rtBody, 0))
    {
        if (m_ptMoveDir.x < 0)
        {
            m_ptMoveDir.x = 0;
        }
    }
    if (m_map.IsRectOutside(&m_rtBody, 1))
    {
        if (m_ptMoveDir.x > 0)
        {
            m_ptMoveDir.x = 0;
        }
    }

    if (IsStop)
    {
        m_ptMoveDir.x = 0;
        m_ptMoveDir.y = 0;
    }
}

Bullet Player::Shot(int BulletSpeed, HBRUSH Brush)
{
    g_pLog4K->WriteLog(EL_INFO, "SHOT");
    Bullet shotBullet;
    shotBullet.SetBodyRect(GetTurretPos());
    shotBullet.SetMoveDir(POINT{ 0, -BulletSpeed });
    shotBullet.SetBrush(Brush);
    shotBullet.m_isHit = false;

    return shotBullet;
}

POINT Player::GetTurretPos()
{
    POINT ptTurret;
    ptTurret.x = m_rtBody.left + (int)(PLAYER_SIZE * 0.5);
    ptTurret.y = m_rtBody.top;
    return ptTurret;
}
