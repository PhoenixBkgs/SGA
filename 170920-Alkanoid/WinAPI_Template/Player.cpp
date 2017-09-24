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
    m_isRender = true;
    m_angle = 90.0f;
    m_speed = 50.0f;
    SetBodyRect(UnitPos{ 0, 0 }, UnitSize{ 100, 40 });
    SetColor(0, 0, 0);
}

void Player::Update()
{
    Move();
    m_barDestPos = m_geoHelper.GetCoordFromAngle(m_angle, m_speed);
    m_barDestPos.x += m_unitPos.x;
    m_barDestPos.y += m_unitPos.y;
}

void Player::Render()
{
    Draw(SHAPE_RECT, true);
    m_drawHelper.DrawLine2D(m_unitPos, m_barDestPos, 1, RGBA{ 0, 0, 0, 0 });
}
