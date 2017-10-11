#include "stdafx.h"
#include "Player.h"


Player::Player()
{
    m_unitPos.x = W_WIDTH  * 0.3f;
    m_unitPos.y = W_HEIGHT * 0.7f;
}


Player::~Player()
{
}

void Player::Start()
{
    m_pImg->SetupForSprites(8, 0, 108, 140, 10);
    m_rtBody = { 0 + (int)m_unitPos.x, 0 + (int)m_unitPos.y, 108 + (int)m_unitPos.x, 140 + (int)m_unitPos.y };
}

void Player::Update()
{
    m_rtBody = { (int)m_unitPos.x, (int)m_unitPos.y, 108 + (int)m_unitPos.x, 140 + (int)m_unitPos.y };
    m_unitPos.y += GRAVITY;
    if (m_unitPos.y > W_HEIGHT * 0.7f)
    {
        m_unitPos.y = W_HEIGHT * 0.7f;
    }
    
    if (m_unitPos.y < 0.0f)
    {
        m_unitPos.y = 0.0f;
    }
}

void Player::Render()
{
    m_pImg->SpritesRender(g_hDC, m_rtBody, 255);
}
