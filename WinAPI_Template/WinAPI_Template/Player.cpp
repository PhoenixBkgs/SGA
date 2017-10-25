#include "stdafx.h"
#include "Player.h"


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

    SpritesObject::Update();
    PlayerController();
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

    if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
    {
        m_dJumpPower = 25.0f;
        m_bIsJump = true;
    }

    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        m_playerState = 1;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_RBUTTON))
    {
        RECT rt = g_pDrawHelper->MakeRect({ (double)g_ptMouse.x, (double)g_ptMouse.y }, { 100, 150 });
        g_pPixelManager->RemoveRect(g_pImgManager->FindImage("land"), rt);
    }

    speed.y -= m_dJumpPower;
    speed.y += m_gravity;
    m_gravity += 0.5f;
    m_dJumpPower -= 1.0f;
    m_dJumpPower = m_dJumpPower < 0.0f ? 0.0f : m_dJumpPower;

    ImageObject*    img = g_pImgManager->FindImage("land");
    if (GetSpeed().y > 0.0f)
    {
        if (g_pPixelManager->CheckPixel(img, (int)GetPos().x, m_rtBody.top) == false)
        {
            
        }
        else
        {
            while (g_pPixelManager->CheckPixel(img, (int)GetPos().x, m_rtBody.bottom) == false)
            {
                UnitPos pos = GetPos();
                pos.y -= 1.0f;
                SetBodyPos(pos);
                m_gravity = 0.0f;
                SetBodyRect(g_pDrawHelper->MakeRect(GetPos(), GetSize()));
            }
        }
    }
    else
    {

    }
    if (g_pPixelManager->CheckPixel(img, GetPos()) == true)     //  중점은 허공에 있을때
    {
        if (speed.x > 0.0f)
        {
            while (g_pPixelManager->CheckPixel(img, m_rtBody.right, (int)GetPos().y) == false)
            {
                UnitPos pos = GetPos();
                pos.x -= 1.0f;
                SetBodyPos(pos);
                SetBodyRect(g_pDrawHelper->MakeRect(GetPos(), GetSize()));
            }
        }
        else if (speed.x < 0.0f)
        {
            while (g_pPixelManager->CheckPixel(img, m_rtBody.left, (int)GetPos().y) == false)
            {
                UnitPos pos = GetPos();
                pos.x += 1.0f;
                SetBodyPos(pos);
                SetBodyRect(g_pDrawHelper->MakeRect(GetPos(), GetSize()));
            }
        }
    }

    SetBodySpeed(speed);
}