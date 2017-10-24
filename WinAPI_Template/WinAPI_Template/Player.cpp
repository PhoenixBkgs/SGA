#include "stdafx.h"
#include "Player.h"


Player::Player()
{
    Setup();
    g_pTimerManager->AddSimpleTimer("player-idle");
}


Player::~Player()
{
}

void Player::Update()
{
    SpritesObject::Update();
    PlayerController();
    if (g_pTimerManager->TickSimpleTimer("player-idle") > 5)
    {
        g_pTimerManager->ResetSimpleTimer("player-idle");
        NextFrameX();
    }
}

void Player::Render()
{
    SpritesObject::Render();
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "posx : %f / posy : %f", m_dPos.x, m_dPos.y);
    TextOut(g_hDC, 0, 10, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}

void Player::PlayerController()
{
    UnitSpeed speed = { 0.0f, 0.0f };
    if (g_pKeyManager->isStayKeyDown(VK_UP))
    {
        speed.y = -5.0f;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
    {
        speed.y = 5.0f;
    }
    if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        speed.x = -5.0f;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        speed.x = 5.0f;
    }
    SetBodySpeed(speed);
}