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
    SpritesObject::Update();
    m_hpBar.SetGaugeRatio(m_dHp / PLAYER_INIT_HP);

    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
    {
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
    genBullet.SetBodySpeed(UnitSpeed{ 0.0f, -15.0f });
    genBullet.SetFrameY(1);
    genBullet.SetHBoxMargin({ 0, 0, 0, 0 });
    genBullet.SetHBox();
    genBullet.SetDamage(-5.0f);

    m_vecBullets.push_back(genBullet);
}
