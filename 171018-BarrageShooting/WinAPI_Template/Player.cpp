#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"

Player::Player()
{

}

Player::Player(string szTagName)
{
    m_weaponType = WEAPON_SINGLESHOT;
    m_szTagName = szTagName;
    SetBodyImgAuto();
    m_dHp = PLAYER_INIT_HP;
    m_vecBullets = NULL;
    g_pTimerManager->AddOnOffTimer("player-immortal", { 0.0f, 0.0f }, 1.0f, 0.5f);
}

Player::~Player()
{
}

void Player::SetupForProgressBar()
{
    m_hpBar.SetBodyPos(UnitPos{ W_WIDTH * 0.5f, W_HEIGHT - 50.0f });
    m_hpBar.SetBodySize(UnitSize{ 500, 50 });
    m_hpBar.SetBodyRect(g_pDrawHelper->MakeRect(m_hpBar.GetPos(), m_hpBar.GetSize()));
    m_hpBar.SetSpritesBack(g_pImgManager->FindImage("hp-frame"));
    m_hpBar.SetSpritesFront(g_pImgManager->FindImage("hp-bar"));
    m_hpBar.SetupSprites();
    m_hpBar.SetIsSetup();
}

void Player::Update()
{
    PlayerController();
    SpritesObject::Update();
    m_hpBar.SetGaugeRatio(m_dHp / PLAYER_INIT_HP);

    if (m_isImmortal)
    {
        if (g_pTimerManager->TickOnOffTimer("player-immortal"))
        {
            m_dAlpha = 128.0f;
        }
        else
        {
            m_dAlpha = 255.0f;
        }
    }
    else
    {
        m_dAlpha = 255.0f;
    }
}

void Player::Render()
{
    SpritesObject::Render();
    m_hpBar.Render(g_hDC);
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "player pos x : %f  /  y : %f", GetPos().x, GetPos().y);
    TextOut(g_hDC, 0, 0, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}

void Player::Shoot()
{
    m_nShootDelay++;
    if (m_nShootDelay > PLAYER_MAX_SHOOT_DELAY)
        m_nShootDelay = 0;
    else
        return;

    Bullet genBullet("player-bullet");
    vector<Bullet> tempVector;
    switch (m_weaponType)
    {
    case WEAPON_SINGLESHOT:
        tempVector = genBullet.SingleShot(GetPos(), -90.0f);
        break;
    case WEAPON_MAGNUM:
        tempVector = genBullet.Magnum(GetPos(), -90.0f);
        break;
    case WEAPON_BUCKSHOT:
        tempVector = genBullet.Buckshot(GetPos(), -90.0f);
        break;
    case WEAPON_BARRAGE:
        tempVector = genBullet.BarrageHD(GetPos(), -90.0f);
        break;
    }

    for (auto iter = tempVector.begin(); iter != tempVector.end(); iter++)
    {
        m_vecBullets->push_back(*iter);
    }
}

void Player::PlayerController()
{
    //  Player sprites mod
    UnitSpeed dPlayerSpd = { 0.0f, 0.0f };
    if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        dPlayerSpd.x = -PLAYER_SPEED;
        SetFrameY(1);
    }
    else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        dPlayerSpd.x = PLAYER_SPEED;
        SetFrameY(2);
    }
    else
    {
        SetFrameY(0);
    }

    if (g_pKeyManager->isStayKeyDown(VK_UP))
    {
        dPlayerSpd.y = -PLAYER_SPEED;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
    {
        dPlayerSpd.y = PLAYER_SPEED;
    }
    SetBodySpeed(dPlayerSpd);

    //  Shoot
    if (g_pKeyManager->isStayKeyDown(VK_SPACE))
    {
        Shoot();
    }

    if (g_pKeyManager->isOnceKeyDown('Q'))
    {
        m_weaponType = WEAPON_SINGLESHOT;
    }
    else if (g_pKeyManager->isOnceKeyDown('W'))
    {
        m_weaponType = WEAPON_MAGNUM;
    }
    else if (g_pKeyManager->isOnceKeyDown('E'))
    {
        m_weaponType = WEAPON_BUCKSHOT;
    }
    else if (g_pKeyManager->isOnceKeyDown('R'))
    {
        m_weaponType = WEAPON_BARRAGE;
    }

    if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
    {
        m_isImmortal = !m_isImmortal;
    }
}
