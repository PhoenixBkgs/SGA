#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
    g_pTimerManager->AddOnOffTimer("roaming", { 0.0f, 0.0f }, 0.01f, 2.0f);
    m_dSpeed.x = -ENEMY_MOVE_SPEED;
    m_destDC = g_pImgManager->FindImage("map-buffer");
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
    m_dPos.x = m_startPos.x + m_destPos.x;
    m_dPos.y = m_startPos.y + m_destPos.y;

    //  COLLISION BOTTOM
    m_startPos.y += m_dSpeed.y;
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
            //m_startPos.x += ENEMY_MOVE_SPEED;
            SetFrameY(1);
        }
        else if (g_pPixelManager->CheckPixel(m_destDC->GetMemDC()
            , (int)m_dPos.x + (int)(m_nSize.w * 0.3f) + (int)(m_dSpeed.x)
            , (int)(m_dPos.y + m_nSize.h * 0.6f)))
        {
            m_dSpeed.x = -ENEMY_MOVE_SPEED;
            //m_startPos.x += -ENEMY_MOVE_SPEED;
            SetFrameY(0);
        }

        //  WALL HANDLE
        if (g_pPixelManager->CheckPixel(m_destDC->GetMemDC()
            , (int)m_dPos.x - (int)(m_nSize.w * 0.5f) + (int)(m_dSpeed.x)
            , (int)(m_dPos.y)) == false)
        {
            m_dSpeed.x = ENEMY_MOVE_SPEED;
            //m_startPos.x += ENEMY_MOVE_SPEED;
            SetFrameY(1);
        }
        else if (g_pPixelManager->CheckPixel(m_destDC->GetMemDC()
            , (int)m_dPos.x + (int)(m_nSize.w * 0.5f) + (int)(m_dSpeed.x)
            , (int)(m_dPos.y)) == false)
        {
            m_dSpeed.x = -ENEMY_MOVE_SPEED;
            //m_startPos.x += -ENEMY_MOVE_SPEED;
            SetFrameY(0);
        }
    }
    else
    {
        m_dSpeed.y = 2.0f;
    }

    m_startPos.x += m_dSpeed.x;

    g_pTimerManager->AddSimpleTimer(m_szTagName);
    if (g_pTimerManager->TickSimpleTimer(m_szTagName) > 5)
    {
        g_pTimerManager->ResetSimpleTimer(m_szTagName);
        NextFrameX();
    }

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
    sprintf_s(infoMsg, "%.0f, %.0f, %.0f", GetBodyPos().x, GetBodyPos().y, m_dMapPos->x);
    TextOut(g_hDC, GetBodyPos().x, GetBodyPos().y, infoMsg, (int)strlen(infoMsg));
}