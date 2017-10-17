#include "stdafx.h"
#include "Player.h"
#include "Arrow.h"

Player::Player()
    : m_dPowerStep(POWER_STEP)
{

}


Player::~Player()
{
}

void Player::Setup()
{
    m_nSize.w = PLAYER_WIDTH;
    m_nSize.h = PLAYER_HEIGHT;
    m_dPos.x = PLAYER_WIDTH * 0.5f;
    m_dPos.y = 600.0f - PLAYER_HEIGHT;
    m_rtBody = g_pDrawHelper->MakeRect(m_dPos, m_nSize);
    m_rtHitBox = m_rtBody;
    m_rtHitBox.top += 300;
    m_rtHitBox.bottom += 300;
}

void Player::Update()
{
}

void Player::Shoot()
{
    UnitPos relativePos;
    UnitPos centerPos = g_pGeoHelper->GetCenterPointWindow();
    relativePos.x = (double)g_ptMouse.x - centerPos.x;
    relativePos.y = (double)g_ptMouse.y - centerPos.y;
    m_pArrow->SetSpeed3D(UnitSpeed3D{ 10.0f, relativePos.x, -relativePos.y });
    m_pArrow->Shoot();
}
