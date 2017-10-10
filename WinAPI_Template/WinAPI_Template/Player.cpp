#include "stdafx.h"
#include "Player.h"


Player::Player()
    :m_idleDelay(10),
    m_idleSpriteIdx(0)
{
    Start();
    m_unitPos.x = W_WIDTH  * 0.5f;
    m_unitPos.y = W_HEIGHT * 0.5f;
}


Player::~Player()
{
}

void Player::Start()
{

}

void Player::Update()
{
}

void Player::Render()
{
    m_idleDelay--;
    if (m_idleDelay < 0)
    {
        m_idleSpriteIdx++;
        m_idleDelay = IDLE_FRAME;
    }

    if (m_idleSpriteIdx > 7)
    {
        m_idleSpriteIdx = 0;
    }

    m_pImg->Render(g_hDC, (int)m_unitPos.x, (int)m_unitPos.y, m_idleSpriteIdx * 108, 0, 108, 140);
}
