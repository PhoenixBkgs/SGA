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
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
    SpritesObject::Update();
    m_nShootDelay++;
    if (m_nShootDelay > MAX_SHOOT_DELAY)
    {
        m_nShootDelay = 0;
        Shoot();
    }

    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
    {
        iter->Update();
    }

    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end();)
    {
        if (iter->GetLife() == 0)
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
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "bullet count : %d", (int)m_vecBullets.size());
    TextOut(g_hDC, 0, 15, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}

void Enemy::Shoot()
{
    if (m_pPlayer == NULL)
        return;

    Bullet genBullet("bullet");
    genBullet.SetBodyPos(GetPos());
    genBullet.SetBodySize(UnitSize{ 32, 32 });
    genBullet.SetBodyRect(g_pDrawHelper->MakeRect(genBullet.GetPos(), genBullet.GetSize()));
    genBullet.SetupForSprites(2, 2);
    genBullet.SetSpritesImg(g_pImgManager->FindImage("bullet"));
    double angle = g_pGeoHelper->GetAngleFromCoord(genBullet.GetPos(), m_pPlayer->GetPos());
    UnitPos pos = g_pGeoHelper->GetCoordFromAngle(angle, 10.0f);
    genBullet.SetBodySpeed((UnitSpeed)pos);

    m_vecBullets.push_back(genBullet);
}


void Enemy::PatternA()
{
}

void Enemy::PatternB()
{
}

void Enemy::PatternC()
{
}
