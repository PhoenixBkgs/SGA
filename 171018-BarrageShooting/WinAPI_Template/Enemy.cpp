#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"


Enemy::Enemy()
    : m_pPlayer(NULL)
{
}

Enemy::Enemy(string szTagName)
{
    m_szTagName = szTagName;
    SetBodyImgAuto();
    m_dHp = BOSS_INIT_HP;
    m_nShootDelayMax = ENEMY_MAX_SHOOT_DELAY;
    m_nCShootMax = -1;
    m_nCShootCount = 0;
    m_bIsReload = true;

    g_pTimerManager->AddOnOffTimer("phase-1");
    g_pTimerManager->AddSimpleTimer("phase-1");
    g_pTimerManager->AddOnOffTimer("phase-2");
    g_pTimerManager->AddSimpleTimer("phase-2");
    g_pTimerManager->AddOnOffTimer("phase-3");
    g_pTimerManager->AddSimpleTimer("phase-3");
    g_pTimerManager->AddOnOffTimer("phase-4");
    g_pTimerManager->AddSimpleTimer("phase-4");
}


Enemy::~Enemy()
{
}

void Enemy::SetupForProgressBar()
{
    m_hpBar.SetBodyPos(UnitPos{ W_WIDTH * 0.5f, 50.0f });
    m_hpBar.SetBodySize(UnitSize{ 500, 50 });
    m_hpBar.SetBodyRect(g_pDrawHelper->MakeRect(m_hpBar.GetPos(), m_hpBar.GetSize()));
    m_hpBar.SetSpritesBack(g_pImgManager->FindImage("hp-frame"));
    m_hpBar.SetSpritesFront(g_pImgManager->FindImage("hp-bar-2"));
    m_hpBar.SetupSprites();
    m_hpBar.SetIsSetup();
}

void Enemy::Update()
{
    SpritesObject::Update();

    double hpRatio = m_dHp / BOSS_INIT_HP;
    m_hpBar.SetGaugeRatio(hpRatio);

    Shoot();
}

void Enemy::Render()
{
    SpritesObject::Render();
    m_hpBar.Render(g_hDC);
}

void Enemy::Shoot()
{
    if (m_pPlayer == NULL)
        return;

    double hpRatio = m_dHp / BOSS_INIT_HP;

    Bullet genBullet("enemy-bullet");
    vector<Bullet> tempVector;
    UnitPos playerPos = m_pPlayer->GetPos();
    double  dAngle = g_pGeoHelper->GetAngleFromCoord(GetPos(), playerPos);
    if (hpRatio > 0.9f)
    {
        if (g_pTimerManager->TickOnOffTimer("phase-1"))
        {
            tempVector = genBullet.SingleShot(GetPos(), dAngle);
        }
    }
    else if (hpRatio > 0.6f)
    {
        if (g_pTimerManager->TickOnOffTimer("phase-2"))
        {
            tempVector = genBullet.Buckshot(GetPos(), dAngle);
        }
    }
    else if (hpRatio > 0.2f)
    {
        if (g_pTimerManager->TickOnOffTimer("phase-3"))
        {
            if (g_pTimerManager->TickSimpleTimer("phase-2") > 50)
            {
                g_pTimerManager->ResetSimpleTimer("phase-2");
                double deltaAngle = g_pTimerManager->FindOnOffTick("phase-1") * 10.0f;
                tempVector = genBullet.BarrageHD(GetPos(), 90.0f + deltaAngle);
            }
            else
            {
                if (g_pTimerManager->TickSimpleTimer("phase-3") > 10)
                {
                    g_pTimerManager->ResetSimpleTimer("phase-3");
                    tempVector = genBullet.Buckshot(GetPos(), dAngle);
                }
            }
        }
    }
    else
    {
        if (g_pTimerManager->TickOnOffTimer("phase-4"))
        {
            if (g_pTimerManager->TickSimpleTimer("phase-3") > 25)
            {
                g_pTimerManager->ResetSimpleTimer("phase-3");
                tempVector = genBullet.BarrageHD(GetPos(), dAngle);
            }
        }
        else
        {
            if (g_pTimerManager->TickSimpleTimer("phase-4") > 5)
            {
                g_pTimerManager->ResetSimpleTimer("phase-4");
                tempVector = genBullet.Buckshot(GetPos(), dAngle);
            }
        }
    }

    for (auto iter = tempVector.begin(); iter != tempVector.end(); iter++)
    {
        m_vecBullets->push_back(*iter);
    }
}