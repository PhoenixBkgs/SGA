#include "stdafx.h"
#include "Player.h"
#include "TileObject.h"

Player::Player()
{
    Setup();
    m_playerState = 0;
    m_dJumpPower = 0.0f;
    m_gravity = 0.0f;
    m_bIsJump = false;
    g_pTimerManager->AddSimpleTimer("player-idle");
    g_pTimerManager->AddSimpleTimer("player-atk");
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
	if (g_pPixelManager->CheckPixel(g_pImgManager->FindImage("map-buffer")->GetMemDC()
								, (int)GetBodyPos().x, (int)GetBodyPos().y + m_nSize.h * 0.5f) == false)
	{
		m_dSpeed.y = 0.0f;
		m_gravity = 0.0f;
	}

	if (m_bIsJump)
	{
		m_dSpeed.y -= JUMP_POWER;
		m_bIsJump = false;
	}
    SpritesObject::Update();
}

void Player::Render()
{
    SpritesObject::Render();
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "posx : %f / posy : %f / framex : %d", m_dPos.x, m_dPos.y, GetFrameX());
    TextOut(g_hDC, 0, 10, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
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

    if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
    {
        m_bIsJump = true;
    }

    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        m_playerState = 1;
    }

    speed.y += m_gravity;
    m_gravity += 0.1f;
    m_dJumpPower -= 1.0f;
    m_dJumpPower = m_dJumpPower < 0.0f ? 0.0f : m_dJumpPower;

    SetBodySpeed(speed);
}