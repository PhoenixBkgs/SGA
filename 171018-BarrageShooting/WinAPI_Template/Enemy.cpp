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
    m_hpBar.SetSpritesFront(g_pImgManager->FindImage("hp-bar"));
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
    m_nShootDelay++;
    if (m_nShootDelay > m_nShootDelayMax)
    {
        m_nShootDelay = 0;
        if (m_bIsReload)
        {
            m_nCShootCount++;
            if (m_nCShootCount > (int)(m_nCShootMax * 0.1f))
            {
                m_nCShootCount = 0;
                m_bIsReload = false;
            }
        }
        else
        {
            Shoot();
            m_nCShootCount++;
            if (m_nCShootCount > m_nCShootMax)
            {
                m_nCShootCount = 0;
                m_bIsReload = true;
            }
        }
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
        PatternB();
    }
    else if (hpRatio > 0.2f)
    {
        PatternA();
        PatternB();
    }
    else
    {
        PatternA();
        PatternB();
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
    double angle = g_pGeoHelper->GetAngleFromCoord(genBullet.GetPos(), m_pPlayer->GetPos());
    UnitPos pos = g_pGeoHelper->GetCoordFromAngle(angle, 10.0f);
    m_nCShootMax = 100;
    genBullet.SetBodySpeed((UnitSpeed)pos);
    genBullet.SetHBoxMargin({ 0, 0, 0, 0 });
    genBullet.SetHBox();

    m_vecBullets.push_back(genBullet);
}

void Enemy::PatternB()
{
    Bullet genBullet("bullet");

    genBullet.SetBodyPos(GetPos());
    genBullet.SetBodySize(UnitSize{ 32, 32 });
    genBullet.SetBodyRect(g_pDrawHelper->MakeRect(genBullet.GetPos(), genBullet.GetSize()));
    genBullet.SetupForSprites(2, 2);
    genBullet.SetSpritesImg(g_pImgManager->FindImage("bullet"));
    double angle = 0.0f;
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
