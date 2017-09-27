#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    Start();
}


MainGame::~MainGame()
{
}

void MainGame::Start()
{
    m_enemyGenDelay = 50;
}

void MainGame::Update()
{
    GameNode::Update();
    m_enemyGenDelay--;
    if (m_enemyGenDelay <= 0)
    {
        GenEnemy();
        m_enemyGenDelay = 50;
    }

    if (g_pKeyManager->isStayKeyDown('A'))
    {
        m_player.m_barrelAngle += 5.0f;
    }
    else if (g_pKeyManager->isStayKeyDown('D'))
    {
        m_player.m_barrelAngle -= 5.0f;
    }

    if (m_player.m_barrelAngle <= 20.0f)
    {
        m_player.m_barrelAngle = 20.0f;
    }
    else if(m_player.m_barrelAngle >= 160.0f)
    {
        m_player.m_barrelAngle = 160.0f;
    }

    if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
    {
        Shoot();
    }

    m_player.Update();

    for (auto bulletUpdateIter = m_vecBullet.begin(); bulletUpdateIter != m_vecBullet.end(); bulletUpdateIter++)
    {
        bulletUpdateIter->Update();
    }

    for (auto enemyUpdateIter = m_vecEnemy.begin(); enemyUpdateIter != m_vecEnemy.end(); enemyUpdateIter++)
    {
        enemyUpdateIter->Update();
    }

    Collider();
    EnemyCleaner();
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
    m_player.Render();

    for (auto bulletDrawIter = m_vecBullet.begin(); bulletDrawIter != m_vecBullet.end(); bulletDrawIter++)
    {
        bulletDrawIter->Render();
    }

    for (auto enemyDrawIter = m_vecEnemy.begin(); enemyDrawIter != m_vecEnemy.end(); enemyDrawIter++)
    {
        enemyDrawIter->Render();
    }
}

void MainGame::Shoot()
{
    Bullet genBullet(m_player.GetBarrelPos());
    genBullet.SetMoveSpeed((UnitSpeed)m_geoHelper.GetCoordFromAngle(m_player.m_barrelAngle, BULLET_SPEED));
    m_vecBullet.push_back(genBullet);
}

void MainGame::GenEnemy()
{
    Enemy genEnemy;
    m_vecEnemy.push_back(genEnemy);
}

void MainGame::Collider()
{
    for (auto bulletCollIter = m_vecBullet.begin(); bulletCollIter != m_vecBullet.end(); bulletCollIter++)
    {
        for (auto enemyCollIter = m_vecEnemy.begin(); enemyCollIter != m_vecEnemy.end(); enemyCollIter++)
        {
            RECT rt;
            if (IntersectRect(&rt, bulletCollIter->GetBodyRect(), enemyCollIter->GetBodyRect()))
            {
                enemyCollIter->m_LifeCount -= 1;
            }
        }
    }
}

void MainGame::EnemyCleaner()
{
    for (auto enemyEraseIter = m_vecEnemy.begin(); enemyEraseIter != m_vecEnemy.end();)
    {
        if (enemyEraseIter->m_LifeCount <= 0)
        {
            enemyEraseIter = m_vecEnemy.erase(enemyEraseIter);
        }
        else
        {
            enemyEraseIter++;
        }
    }
}

//  mouse point



//  get angle



//  shoot bullet


//  collider


//  eraser