#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    Start();
}


MainGame::~MainGame()
{
    delete m_playerBrush;
    delete m_bulletBrush;
    delete m_enemyBrush;
}

void MainGame::Start()
{
    m_isPause = true;
    m_gameLevel = 1;
    m_gameScore = 0;

    m_lifeTimeCount = MAX_TIMER * (m_gameLevel * LEVELING_FACTOR);
    m_isGenEnemy = true;
    m_enemyGenDelay = 100;

    m_playerBrush = new HBRUSH;
    *m_playerBrush = CreateSolidBrush(RGB(120, 120, 120));
    m_bulletBrush = new HBRUSH;
    *m_bulletBrush = CreateSolidBrush(RGB(0, 0, 0));
    m_enemyBrush = new HBRUSH;
    *m_enemyBrush = CreateSolidBrush(RGB(120, 0, 0));


    m_player.SetBrush(m_playerBrush);
}

void MainGame::Update()
{
    if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
    {
        m_isPause = !m_isPause;
    }

    if (m_isPause)
    {
        return;
    }

    m_lifeTimeCount--;
    if (m_lifeTimeCount <= 0)
    {
        return;
    }
    GameNode::Update();
    if (m_enemyGenDelay <= 0 && m_isGenEnemy)
    {
        GenEnemy();
        m_enemyGenDelay = MAX_DELAY;
        m_enemyCount++;
    }
    else if (m_isGenEnemy)
    {
        m_enemyGenDelay -= m_gameLevel;
    }

    if (m_enemyCount >= (10 * m_gameLevel))
    {
        if (m_isGenEnemy)
        {
            m_isGenEnemy = false;
        }
    }

    if (m_vecEnemy.size() <= 0 && m_isGenEnemy == false)
    {
        m_gameLevel++;
        m_enemyGenDelay = MAX_DELAY;
        m_enemyCount = 0;
        m_isPause = true;
        m_isGenEnemy = true;
        m_lifeTimeCount = MAX_TIMER * (m_gameLevel * 0.5);
        m_vecBullet.clear();
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
        if (bulletUpdateIter->GetBodyRect()->bottom <= -10)
        {
            bulletUpdateIter->m_LifeCount = 0;
            m_lifeTimeCount -= 50 * m_gameLevel;
        }
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

    if (m_isPause)
    {
        char str[100];
        sprintf_s(str, "LEVEL : %d", m_gameLevel);
        TextOut(g_hDC, W_WIDTH * 0.5, W_HEIGHT * 0.5, str, strlen(str));
        return;
    }
    else
    {
    }

    m_player.Render();

    for (auto bulletDrawIter = m_vecBullet.begin(); bulletDrawIter != m_vecBullet.end(); bulletDrawIter++)
    {
        bulletDrawIter->Render();
    }

    for (auto enemyDrawIter = m_vecEnemy.begin(); enemyDrawIter != m_vecEnemy.end(); enemyDrawIter++)
    {
        enemyDrawIter->Render();
    }

    char str[100];
    sprintf_s(str, "GAME SCORE : %d         GAME LEVEL %d                  TIEM REMAIN : %d", m_gameScore, m_gameLevel, m_lifeTimeCount);
    TextOut(g_hDC, 10, 10, str, strlen(str));
}

void MainGame::Shoot()
{
    Bullet genBullet(m_player.GetBarrelPos());
    genBullet.SetBrush(m_bulletBrush);
    genBullet.SetMoveSpeed((UnitSpeed)m_geoHelper.GetCoordFromAngle(m_player.m_barrelAngle, BULLET_SPEED));
    m_vecBullet.push_back(genBullet);
}

void MainGame::GenEnemy()
{
    Enemy genEnemy;
    genEnemy.SetBrush(m_enemyBrush);
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
                m_gameScore += enemyCollIter->m_score;
                enemyCollIter->m_LifeCount -= bulletCollIter->m_LifeCount;
                bulletCollIter->m_LifeCount -= enemyCollIter->m_LifeCount;
                m_lifeTimeCount += 25;
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

    for (auto bulletEraseIter = m_vecBullet.begin(); bulletEraseIter != m_vecBullet.end();)
    {
        if (bulletEraseIter->m_LifeCount <= 0)
        {
            bulletEraseIter = m_vecBullet.erase(bulletEraseIter);
        }
        else
        {
            bulletEraseIter++;
        }
    }
}