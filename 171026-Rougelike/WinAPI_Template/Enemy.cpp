#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
    g_pTimerManager->AddSimpleTimer("enemy");
    g_pTimerManager->AddOnOffTimer("roaming", { 0.0f, 0.0f }, 0.01f, 2.0f);
    m_dSpeed.x = -ENEMY_MOVE_SPEED;
    m_destDC = g_pImgManager->FindImage("map-buffer");
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
    m_startPos.x += m_dSpeed.x;
    m_startPos.y += m_dSpeed.y;

    m_dPos.x = m_startPos.x + m_dMapPos->x;
    m_dPos.y = m_startPos.y + m_dMapPos->y;
    
    //  COLLISION BOTTOM
    m_dSpeed.y = 2.0f;
    if (g_pPixelManager->CheckPixel(m_destDC->GetMemDC()
        , (int)m_dPos.x, (int)m_dPos.y + (int)(m_nSize.h * 0.5f) + (int)(m_dSpeed.y)) == false)
    {
        m_dSpeed.y = 0.0f;

        //  CLIFF HANDLE
        if (g_pPixelManager->CheckPixel(m_destDC->GetMemDC()
            , (int)m_dPos.x - (int)(m_nSize.w * 0.3f) + (int)(m_dSpeed.x)
            , (int)(m_dPos.y + m_nSize.h * 0.6f)))
        {
            m_dSpeed.x = ENEMY_MOVE_SPEED;
            SetFrameY(1);
        }
        else if (g_pPixelManager->CheckPixel(m_destDC->GetMemDC()
            , (int)m_dPos.x + (int)(m_nSize.w * 0.3f) + (int)(m_dSpeed.x)
            , (int)(m_dPos.y + m_nSize.h * 0.6f)))
        {
            m_dSpeed.x = -ENEMY_MOVE_SPEED;
            SetFrameY(0);
        }

        //  WALL HANDLE
        if (g_pPixelManager->CheckPixel(m_destDC->GetMemDC()
            , (int)m_dPos.x - (int)(m_nSize.w * 0.5f) + (int)(m_dSpeed.x)
            , (int)(m_dPos.y)) == false)
        {
            m_dSpeed.x = ENEMY_MOVE_SPEED;
            SetFrameY(1);
        }
        else if (g_pPixelManager->CheckPixel(m_destDC->GetMemDC()
            , (int)m_dPos.x + (int)(m_nSize.w * 0.5f) + (int)(m_dSpeed.x)
            , (int)(m_dPos.y)) == false)
        {
            m_dSpeed.x = -ENEMY_MOVE_SPEED;
            SetFrameY(0);
        }
    }

    if (g_pTimerManager->TickSimpleTimer("enemy") > 5)
    {
        g_pTimerManager->ResetSimpleTimer("enemy");
        NextFrameX();
    }

    /*
    if (g_pTimerManager->TickOnOffTimer("roaming"))
    {
        m_dSpeed.x = -ENEMY_MOVE_SPEED;
    }
    else
    {
        m_dSpeed.x = ENEMY_MOVE_SPEED;
    }
    */

    SpritesObject::Update();
}

void Enemy::Render()
{
    if (m_isVisible == true)
    {
        if (m_imgBody != NULL)
        {
            m_imgBody->SpritesRender(m_destDC->GetMemDC(), m_rtBody, m_currFrameX, m_currFrameY, m_dAlpha);
        }
    }
    GameObject::Render();

    char infoMsg[128];
    sprintf_s(infoMsg, "%.0f, %.0f", GetBodyPos().x, GetBodyPos().y);
    TextOut(g_hDC, GetBodyPos().x, GetBodyPos().y, infoMsg, (int)strlen(infoMsg));
    sprintf_s(infoMsg, "%.0f, %.0f", m_dSpeed.x, m_dSpeed.y);
    TextOut(g_hDC, GetBodyPos().x, GetBodyPos().y + 20, infoMsg, (int)strlen(infoMsg));
}