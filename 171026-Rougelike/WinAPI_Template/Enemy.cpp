#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
    g_pTimerManager->AddSimpleTimer("enemy");
    m_dSpeed.x = 2.5f;
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
    ImageObject*	mapBuffer = g_pImgManager->FindImage("map-buffer");
    UnitSpeed speed = { 0.0f, 0.0f };
    speed.x = GetBodySpeed().x;

    if (g_pPixelManager->CheckPixel(mapBuffer->GetMemDC()
        , (int)m_dPos.x, (int)m_dPos.y + (int)(m_nSize.h * 0.5f) + (int)(m_dSpeed.y)) == false)
    {
        m_dSpeed.y = 0.0f;
        m_dPos.y -= 0.5f;
    }
    else
    {
        m_dPos.y += 0.5f;
    }

    if (g_pPixelManager->CheckPixel(mapBuffer->GetMemDC()
        , (int)m_dPos.x - (int)(m_nSize.w * 0.5f) + (int)(m_dSpeed.x), (int)(m_dPos.y + m_nSize.h * 0.5f)))
    {
        m_dSpeed.x = -m_dSpeed.x;
        SetFrameY(1);
    }
    else if (g_pPixelManager->CheckPixel(mapBuffer->GetMemDC()
        , (int)m_dPos.x + (int)(m_nSize.w * 0.5f) + (int)(m_dSpeed.x), (int)(m_dPos.y + m_nSize.h * 0.5f)))
    {
        m_dSpeed.x = -m_dSpeed.x;
        SetFrameY(0);
    }

    if (g_pTimerManager->TickSimpleTimer("enemy") > 5)
    {
        NextFrameX();
    }

    SetBodySpeed(speed);
    SpritesObject::Update();
}

void Enemy::Render()
{
    SpritesObject::Render();

    char infoMsg[128];
    sprintf_s(infoMsg, "%.0f, %.0f", GetBodyPos().x, GetBodyPos().y);
    TextOut(g_hDC, GetBodyPos().x, GetBodyPos().y, infoMsg, (int)strlen(infoMsg));
    sprintf_s(infoMsg, "%.0f, %.0f", m_dSpeed.x, m_dSpeed.y);
    TextOut(g_hDC, GetBodyPos().x, GetBodyPos().y + 20, infoMsg, (int)strlen(infoMsg));
}