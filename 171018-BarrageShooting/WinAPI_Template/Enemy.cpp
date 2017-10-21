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
    double hpRatio = m_dHp / BOSS_INIT_HP;
    if (hpRatio > 0.9f)
    {
        //PatternA();
    }
    else if (hpRatio > 0.6f)
    {
        //PatternB();
    }
    else
    {
        //PatternC();
    }

    SpritesObject::Update();
    m_hpBar.SetGaugeRatio(hpRatio);

    g_pTimerManager->AddSimpleTimer("bShootDelay");
    if (g_pTimerManager->TickSimpleTimer("bShootDelay") > m_nShootDelayMax)
    {
        Shoot();
        g_pTimerManager->ResetSimpleTimer("bShootDelay");
    }

    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
    {
        iter->Update();
        if (m_pPlayer != NULL)
        {
            if (iter->IsAlive())
            {
                RECT rt;
                if (IntersectRect(&rt, &iter->GetHBoxRect(), &m_pPlayer->GetHBoxRect()))
                {
                    m_pPlayer->SumHp(iter->GetDamage());
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

void Enemy::Render()
{
    SpritesObject::Render();
    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
    {
        iter->Render();
    }
    m_hpBar.Render(g_hDC);
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "enemy bullet count : %d // HEALTH : %f", (int)m_vecBullets.size(), GetHp());
    TextOut(g_hDC, 0, 15, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}

void Enemy::Shoot()
{
    if (m_pPlayer == NULL)
        return;

    double hpRatio = m_dHp / BOSS_INIT_HP;
    if (hpRatio > 0.9f)
    {
        PatternA();
    }
    else if (hpRatio > 0.6f)
    {
        static double angle = 0.0f;
        angle += 1.0f;
        PatternB(90.0f + sinf((float)angle) * 10.0f);
    }
    else if (hpRatio > 0.2f)
    {
        PatternA();
        PatternB(90.0f);
    }
    else
    {
        static double angle = 90.0f;
        angle += 10.0f;
        PatternA();
        PatternB(angle);
        PatternC();
    }
}


void Enemy::PatternA()
{
    Bullet genBullet("bullet");

    genBullet.SetBodyPos(GetPos());
    genBullet.SetBodySize(UnitSize{ 32, 32 });
    genBullet.SetBodyRect(g_pDrawHelper->MakeRect(genBullet.GetPos(), genBullet.GetSize()));
    genBullet.SetupForSprites(2, 2);
    genBullet.SetSpritesImg(g_pImgManager->FindImage("bullet"));
    double dist = g_pGeoHelper->GetDistance(m_pPlayer->GetPos(), genBullet.GetPos());
    double angle = g_pGeoHelper->GetAngleFromCoord(genBullet.GetPos(), m_pPlayer->GetPos());
    UnitPos pos = g_pGeoHelper->GetCoordFromAngle(angle, 10.0f);
    
    m_nCShootMax = 100;
    genBullet.SetBodySpeed((UnitSpeed)pos);
    genBullet.SetHBoxMargin({ 0, 0, 0, 0 });
    genBullet.SetHBox();

    m_vecBullets.push_back(genBullet);
}

void Enemy::PatternB(double angle)
{
    Bullet genBullet("bullet");

    genBullet.SetBodyPos(GetPos());
    genBullet.SetBodySize(UnitSize{ 32, 32 });
    genBullet.SetBodyRect(g_pDrawHelper->MakeRect(genBullet.GetPos(), genBullet.GetSize()));
    genBullet.SetupForSprites(2, 2);
    genBullet.SetSpritesImg(g_pImgManager->FindImage("bullet"));
    
    UnitPos pos = g_pGeoHelper->GetCoordFromAngle(angle, 10.0f);
    genBullet.SetBodySpeed((UnitSpeed)pos);
    genBullet.SetHBoxMargin({ 0, 0, 0, 0 });
    genBullet.SetHBox();
    m_nCShootMax = 10;
    m_vecBullets.push_back(genBullet);

    pos = g_pGeoHelper->GetCoordFromAngle(angle + 10.0f, 10.0f);
    genBullet.SetBodySpeed((UnitSpeed)pos);
    m_vecBullets.push_back(genBullet);
    
    pos = g_pGeoHelper->GetCoordFromAngle(angle - 10.0f, 10.0f);
    genBullet.SetBodySpeed((UnitSpeed)pos);
    m_vecBullets.push_back(genBullet);

    g_pTimerManager->AddSimpleTimer("phase-2");
    if (g_pTimerManager->TickSimpleTimer("phase-2") > 10)
    {
        g_pTimerManager->ResetSimpleTimer("phase-2");
        PatternB(-15.0f + angle);
        PatternB(15.0f + angle);
    }    
}

void Enemy::PatternC()
{
    Bullet genBullet("bullet");

    genBullet.SetBodyPos(GetPos());
    genBullet.SetBodySize(UnitSize{ 32, 32 });
    genBullet.SetBodyRect(g_pDrawHelper->MakeRect(genBullet.GetPos(), genBullet.GetSize()));
    genBullet.SetupForSprites(2, 2);
    genBullet.SetSpritesImg(g_pImgManager->FindImage("bullet"));
    double angle = g_pGeoHelper->GetAngleFromCoord(genBullet.GetPos(), m_pPlayer->GetPos());
    double speed = 5.0f;
    double dAngle = 25.0f;
    m_nShootDelayMax = 5;
    m_nCShootMax = 20;

    UnitPos pos = g_pGeoHelper->GetCoordFromAngle(angle, speed);
    genBullet.SetBodySpeed((UnitSpeed)pos);
    genBullet.SetHBoxMargin({ 0, 0, 0, 0 });
    genBullet.SetHBox();
    m_vecBullets.push_back(genBullet);

    pos = g_pGeoHelper->GetCoordFromAngle(angle + dAngle, speed);
    genBullet.SetBodySpeed((UnitSpeed)pos);
    m_vecBullets.push_back(genBullet);

    pos = g_pGeoHelper->GetCoordFromAngle(angle - dAngle, speed);
    genBullet.SetBodySpeed((UnitSpeed)pos);
    m_vecBullets.push_back(genBullet);
}
