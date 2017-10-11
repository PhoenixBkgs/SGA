#include "stdafx.h"
#include "Player.h"
#include "Obstacle.h"

Player::Player()
{
    m_unitPos.x = W_WIDTH  * 0.3f;
    m_unitPos.y = W_HEIGHT * 0.7f;
    m_currDownForce = 5.0f;
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

    //  APPLY GRAVITY
    m_unitPos.y += m_currDownForce;
    m_currDownForce *= 1.009f;
    if (m_currDownForce > GRAVITY)
    {
        m_currDownForce = GRAVITY;
    }

    if (m_unitPos.y > W_HEIGHT * 0.7f)
    {
        m_unitPos.y = W_HEIGHT * 0.7f;
        m_currDownForce = 1.0f;
    }
    
    if (m_unitPos.y < 0.0f)
    {
        m_unitPos.y = 0.0f;
    }

    //  COLLISION
    for (auto obsIter = m_vecObstacles->begin(); obsIter != m_vecObstacles->end(); obsIter++)
    {
        RECT rt;
        if (IntersectRect(&rt, &m_rtBody, obsIter->GetBodyRect()))
        {
            if (obsIter->GetLifeCount() > 0)
            {
                //  HAS COLLISION
                m_LifeCount -= 1;
            }
            obsIter->SetLifeCount(0);
        }
    }
}

void Player::Render()
{
    m_pImg->SpritesRender(g_hDC, m_rtBody, 255);
}
