#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"

Player::Player()
{
}

Player::Player(string szTagName)
{
    m_szTagName = szTagName;
    SetBodyImgAuto();
    m_dHp = PLAYER_INIT_HP;
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

    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
    {
        /*
        double pX = g_ptMouse.x < 0 ? 0 : g_ptMouse.x;
        pX = g_ptMouse.x > W_WIDTH ? W_WIDTH : g_ptMouse.x;
        double pY = g_ptMouse.y < 0 ? 0: g_ptMouse.y;
        pY = g_ptMouse.y > W_HEIGHT ? W_HEIGHT : g_ptMouse.y;
        UnitPos viaPos = { pX, pY };
        UnitPos startPos = iter->GetStartPos();
        UnitPos destPos = iter->GetDestPos();
        UnitPos* pos = iter->GetPosRef();
        g_pGeoHelper->BezierInterpolation(*pos, startPos, viaPos, destPos, iter->m_t);
        iter->SetBodyPos(*pos);
        iter->m_t += 0.005f;
        */
        if (iter->m_t > 360.0f)
        {
            iter->m_t = 0.0f;
        }
        iter->m_t += 0.15f;
        float dX = sinf(iter->m_t);
        dX *= 50.0f;
        iter->SetBodyPos({ iter->GetStartPos().x + dX, iter->GetPos().y - (iter->m_t * 0.0001f) });
        /*
        */
        iter->Update();
        if (m_pEnemy != NULL)
        {
            if (iter->IsAlive())
            {
                RECT rt;
                if (IntersectRect(&rt, &iter->GetHBoxRect(), &m_pEnemy->GetHBoxRect()))
                {
                    m_pEnemy->SumHp(iter->GetDamage());
                    iter->SetDead();
                }
            }
        }
    }

    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end();)
    {
        if (iter->IsAlive() == false)
        {
            iter = m_vecBullets.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

void Player::Render()
{
    SpritesObject::Render();
    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
    {
        iter->Render();
    }
    m_hpBar.Render(g_hDC);

#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "player pos x : %f  /  y : %f", GetPos().x, GetPos().y);
    TextOut(g_hDC, 0, 0, infoMsg, (int)strlen(infoMsg));
    sprintf_s(infoMsg, "player bullet count : %d // HEALTH : %d", (int)m_vecBullets.size(), GetLife());
    TextOut(g_hDC, 0, 30, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}

void Player::Shoot()
{
    m_nShootDelay++;
    if (m_nShootDelay > PLAYER_MAX_SHOOT_DELAY)
        m_nShootDelay = 0;
    else
        return;

    Bullet genBullet("bullet");
    genBullet.SetBodyPos(GetPos());
    genBullet.SetBodySize(UnitSize{ 32, 32 });
    genBullet.SetBodyRect(g_pDrawHelper->MakeRect(genBullet.GetPos(), genBullet.GetSize()));
    genBullet.SetupForSprites(2, 2);
    genBullet.SetSpritesImg(g_pImgManager->FindImage("bullet"));
    genBullet.SetBodySpeed(UnitSpeed{ 0.0f, -5.0f });
    genBullet.SetFrameY(1);
    genBullet.SetHBoxMargin({ 0, 0, 0, 0 });
    genBullet.SetHBox();
    genBullet.SetDamage(-5.0f);
    genBullet.SetStartPos(GetPos());
    genBullet.SetDestPos({ GetPos().x, 0.0f });
    genBullet.m_t = 0.0f;

    m_vecBullets.push_back(genBullet);
}

void Player::PlayerController()
{
    //  Player sprites mod
    UnitSpeed dPlayerSpd = { 0.0f, 0.0f };
    SetFrameY(0);
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
}
