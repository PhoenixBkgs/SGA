#include "stdafx.h"
#include "Player.h"
#include "TileObject.h"

Player::Player()
{
    Setup();
    m_ePlayerBuff = NORMAL;
    m_isClear = false;
    m_playerState = 0;
    m_dJumpPower = 0.0f;
    m_gravity = 0.0f;
    m_dBoosterGauge = 50.0f;
    m_bIsJump = false;
    m_isBoosterOn = true;
    g_pTimerManager->AddSimpleTimer("player-idle");
    g_pTimerManager->AddSimpleTimer("player-fly");
    g_pTimerManager->AddSimpleTimer("player-walking");
    g_pTimerManager->AddSimpleTimer("player-immortal");
    g_pTimerManager->AddOnOffTimer("player-immortal-blink", { 0.0f, 0.0f }, 1.0f, 1.0f);
    g_pTimerManager->AddSimpleTimer("player-booster");
}


Player::~Player()
{
}

void Player::Update()
{
    switch (m_playerState)
    {
    case 0:
    {
        SetFrameY(3);
        if (g_pTimerManager->TickSimpleTimer("player-idle") > 5)
        {
            g_pTimerManager->ResetSimpleTimer("player-idle");
            NextFrameX(); 
            if (GetFrameX() > 9)
            {
                SetFrameX(0);
            }
        }
        else
        {
            if (GetFrameX() > 9)
            {
                SetFrameX(0);
            }
        }
        break;
    }
    case 1:
    {
        SetFrameY(1);
        if (g_pTimerManager->TickSimpleTimer("player-fly") > 5)
        {
            g_pTimerManager->ResetSimpleTimer("player-fly");
            NextFrameX();
            if (GetFrameX() > 2)
            {
                SetFrameX(0);
            }
        }
        else
        {
            if (GetFrameX() > 2)
            {
                SetFrameX(0);
            }
        }
        break;
    }
    case 2:
    {
        SetFrameY(4); 
        if (g_pTimerManager->TickSimpleTimer("player-walking") > 2)
        {
            g_pTimerManager->ResetSimpleTimer("player-walking");
            NextFrameX();
            if (GetFrameX() > 7)
            {
                SetFrameX(0);
            }
        }
        else
        {
            if (GetFrameX() > 7)
            {
                SetFrameX(0);
            }
        }
        break;
    }
    }

    PlayerController();
	ImageObject*	mapBuffer = g_pImgManager->FindImage("map-buffer");

    //  COLLISION LEFT
	if (g_pPixelManager->CheckPixel(mapBuffer->GetMemDC()
		, (int)m_dPos.x - (int)(m_nSize.w * 0.5f) + (int)(m_dSpeed.x), (int)(m_dPos.y))== false)
	{	
		m_dSpeed.x = 1.0f;
	}

    //  COLLISION RIGHT
	if (g_pPixelManager->CheckPixel(mapBuffer->GetMemDC()
		, (int)m_dPos.x + (int)(m_nSize.w * 0.5f) + (int)(m_dSpeed.x), (int)(m_dPos.y)) == false)
	{
		m_dSpeed.x = -1.0f;
	}

	if (g_pPixelManager->CheckPixel(mapBuffer->GetMemDC()
		, (int)m_dPos.x, (int)m_dPos.y - (int)(m_nSize.h * 0.5f) + (int)(m_dSpeed.y)) == false)
	{
		m_dSpeed.y = 0.0f;
		m_dJumpPower = 0.0f;
	}
	if (g_pPixelManager->CheckPixel(mapBuffer->GetMemDC()
		, (int)m_dPos.x, (int)m_dPos.y + (int)(m_nSize.h * 0.5f) + (int)(m_dSpeed.y)) == false)
	{
        m_dJumpPower += 1.0f;
        if (m_dJumpPower > 10.0f)
        {
            m_dJumpPower = 10.0f;
        }
        m_dPos.y -= 0.5f;
		m_dSpeed.y = 0.0f;
		m_gravity = 0.0f;
	}

	if (m_bIsJump)
	{
		m_dJumpPower = JUMP_POWER;
		m_bIsJump = false;
	}

    if (m_isImmortal)
    {
        if (g_pTimerManager->TickOnOffTimer("player-immortal-blink"))
        {
            m_dAlpha = 255;
        }
        else
        {
            m_dAlpha = 128;
        }

        if (g_pTimerManager->TickSimpleTimer("player-immortal") > 200)
        {
            g_pTimerManager->ResetSimpleTimer("player-immortal");
            m_isImmortal = false;
            m_ePlayerBuff = NORMAL;
            m_dAlpha = 255;
        }
    }

    for (auto iter = m_vecGameObjs->begin(); iter != m_vecGameObjs->end(); iter++)
    {
        if (iter->GetTagName() == "spike")
        {
            RECT rt;
            if (IntersectRect(&rt, &iter->GetHBoxRect(), &m_rtHitBox))
            {
                SetDead();
            }
        }

        if (iter->GetTagName() == "item-dash")
        {
            RECT rt;
            if (IntersectRect(&rt, &iter->GetHBoxRect(), &m_rtHitBox))
            {
                SumBodySpeedX(200.0f);
                iter->SetDead();
            }
        }

        if (iter->GetTagName() == "item-immortal")
        {
            RECT rt;
            if (IntersectRect(&rt, &iter->GetHBoxRect(), &m_rtHitBox))
            {
                g_pTimerManager->ResetSimpleTimer("player-immortal");
                m_ePlayerBuff = IMMORTAL;
                m_isImmortal = true;
                iter->SetDead();
            }
        }

        if (iter->GetTagName() == "item-dead")
        {

        }

        if (iter->GetTagName() == "goal")
        {
            RECT rt;
            if (IntersectRect(&rt, &iter->GetHBoxRect(), &m_rtHitBox))
            {
                m_isClear = true;
            }
        }
    }
    SpritesObject::Update();
}

void Player::Render()
{
    SpritesObject::Render(); 
#ifdef _DEBUG
	char infoMsg[128];
	sprintf_s(infoMsg, "%d / %d", m_rtBody.left, m_rtBody.right);
	TextOut(g_hDC, m_rtBody.left, m_rtBody.top, infoMsg, (int)strlen(infoMsg));
#endif
}

void Player::PlayerController()
{
    m_playerState = 0;
    UnitSpeed speed = { 0.0f, 0.0f };
	speed.x = GetBodySpeed().x;
    if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        m_playerState = 2;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        m_playerState = 2;
    }

    if (g_pKeyManager->isStayKeyDown(VK_SPACE) && m_isBoosterOn)
    {
        m_playerState = 1;
        speed.y = -10.0f;
        m_dBoosterGauge -= 0.5f;
        if (m_dBoosterGauge < 0.0f)
        {
            m_dBoosterGauge = 0.0f;
            m_isBoosterOn = false;
        }
    }
    else
    {
        m_dBoosterGauge += 0.4f;
        if (m_dBoosterGauge > 50.0f)
        {
            m_isBoosterOn = true;
            m_dBoosterGauge = 50.0f;
        }
    }

    speed.y += m_gravity;
    m_gravity += 0.05f;
    
    SetBodySpeed(speed);
}