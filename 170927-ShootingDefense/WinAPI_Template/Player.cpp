#include "stdafx.h"
#include "Player.h"


Player::Player()
{
    Start();
}


Player::~Player()
{
}

void Player::Start()
{
    m_barrelAngle = 90.0f;
    m_unitPos = { (double)PLAYER_SPAWN_X, (double)PLAYER_SPAWN_Y };
    m_unitSize = { PLAYER_WIDTH, PLAYER_HEIGHT };
    SetBodyRect(m_unitPos, m_unitSize);
    
    m_barrelLength = 50.0f;
    m_barrelPos[0] = { PLAYER_SPAWN_X, PLAYER_SPAWN_Y - 25 };
    m_barrelPos[1] = { m_barrelPos[0].x, m_barrelPos[0].y - m_barrelLength };
}

void Player::Update()
{
    m_barrelPos[1] = m_geoHelper.GetCoordFromAngle(m_barrelAngle, m_barrelLength);
    m_barrelPos[1].x += m_barrelPos[0].x;
    m_barrelPos[1].y += m_barrelPos[0].y;
}

void Player::Render()
{
    //m_drawHelper.DrawShape(SHAPE_RECT, m_unitPos, m_unitSize, _RGBA{ 100, 100, 100, 0 });
    Rectangle(g_hDC, m_rtBody.left, m_rtBody.top, m_rtBody.right, m_rtBody.bottom);
    FillRect(g_hDC, &m_rtBody, *m_bBrush);
    m_drawHelper.DrawLine2D(m_barrelPos[0], m_barrelPos[1], 5, _RGBA{ 0, 0, 0, 0 });
}
