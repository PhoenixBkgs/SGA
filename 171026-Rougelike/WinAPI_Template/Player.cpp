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
    m_bIsJump = false;
    g_pTimerManager->AddSimpleTimer("player-idle");
    g_pTimerManager->AddSimpleTimer("player-atk");
    g_pTimerManager->AddSimpleTimer("player-immortal");
    g_pTimerManager->AddOnOffTimer("player-immortal-blink", { 0.0f, 0.0f }, 1.0f, 1.0f);
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
        SetFrameY(0);
        if (g_pTimerManager->TickSimpleTimer("player-idle") > 5)
        {
            g_pTimerManager->ResetSimpleTimer("player-idle");
            NextFrameX();
        }
        break;
    }
    case 1:
    {
        SetFrameY(1);
        if (g_pTimerManager->TickSimpleTimer("player-atk") > 10)
        {
            g_pTimerManager->ResetSimpleTimer("player-atk");
            NextFrameX();
            if (GetFrameX() > 1)
            {
                SetFrameX(0);
            }
        }
        else
        {
            if (GetFrameX() > 1)
            {
                SetFrameX(0);
            }
        }
        break;
    }
    default:
        break;
    }

    PlayerController();
	ImageObject*	mapBuffer = g_pImgManager->FindImage("map-buffer");

	cout << m_dPos.x - m_nSize.w * 0.5f << endl;
	if (g_pPixelManager->CheckPixel(mapBuffer->GetMemDC()
		, (int)m_dPos.x - (int)(m_nSize.w * 0.5f) + (int)(m_dSpeed.x), (int)(m_dPos.y))== false)
	{
		cout << "left collision" << endl;
		
		m_dSpeed.x = 1.0f;
	}

	if (g_pPixelManager->CheckPixel(mapBuffer->GetMemDC()
		, (int)m_dPos.x + (int)(m_nSize.w * 0.5f) + (int)(m_dSpeed.x), (int)(m_dPos.y)) == false)
	{
		cout << "right collision" << endl;
		
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
		m_dSpeed.y = 0.0f;
		m_gravity = 0.0f;
		m_dJumpPower = 0.0f;
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

        if (iter->GetTagName() == "item-jump")
        {

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
    if (g_pKeyManager->isStayKeyDown(VK_UP))
    {
        speed.y = -5.0f;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
    {
        speed.y = 5.0f;
    }

    if (g_pKeyManager->isStayKeyDown(VK_SPACE) && m_bIsJump == false)
    {
        m_bIsJump = true;
    }

    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        m_playerState = 1;
    }

	speed.y -= m_dJumpPower;
    speed.y += m_gravity;
    m_gravity += 0.5f;
    m_dJumpPower -= 1.0f;
    m_dJumpPower = m_dJumpPower < 0.0f ? 0.0f : m_dJumpPower;

    SetBodySpeed(speed);
}