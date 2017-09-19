#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    Setup();
}


MainGame::~MainGame()
{
}

void MainGame::Update()
{
    PlayerControl();
    if (m_isPlaying == false)
    {
        return;
    }
    GameNode::Update();
    m_player.Move();
    for (auto bulletIter = m_vecBullet.begin(); bulletIter != m_vecBullet.end();)
    {
        bulletIter->Move();
        for (auto enemyIterColl = m_vecEnemy.begin(); enemyIterColl != m_vecEnemy.end();)
        {
            RECT tRt1 = *bulletIter->GetBodyRect();
            RECT tRt2 = *enemyIterColl->GetBodyRect();

            if (m_map.IsCollision(&tRt1, &tRt2))
            {
                bulletIter->m_isHit = true;
                enemyIterColl = m_vecEnemy.erase(enemyIterColl);
                break;
            }
            else
            {
                enemyIterColl++;
            }
        }

        if (m_map.IsBulletArrive(bulletIter->GetBodyRect()) ||
            bulletIter->m_isHit)
        {
            //  BULLET END
            bulletIter = m_vecBullet.erase(bulletIter);
        }
        else
        {
            bulletIter++;
        }
    }

    E_EDGE collEdge;
    for (auto enemyIterMove = m_vecEnemy.begin(); enemyIterMove != m_vecEnemy.end(); enemyIterMove++)
    {
        collEdge = enemyIterMove->IsInsideWindow(false);
        switch (collEdge)
        {
        case LEFT_EDGE:
        case RIGHT_EDGE:
            m_isEnemyArriveWall = true;
            break;
        case BOTTOM_EDGE:
            //  GAME OVER
            m_isPlaying = false;
            break;
        }
        if (m_isEnemyArriveWall)
        {
            break;
        }
    }

    if (m_isEnemyArriveWall)
    {
        for (auto enemyIterMove = m_vecEnemy.begin(); enemyIterMove != m_vecEnemy.end(); enemyIterMove++)
        {
            POINT ptEnemyMoveDir = enemyIterMove->GetMoveDir();
            ptEnemyMoveDir.x = -ptEnemyMoveDir.x;
            enemyIterMove->m_rtBody.top += ENEMY_SPEED;
            enemyIterMove->m_rtBody.bottom += ENEMY_SPEED;
            enemyIterMove->SetMoveDir(ptEnemyMoveDir);
        }
        m_isEnemyArriveWall = false;
    }

    for (auto enemyIterMove = m_vecEnemy.begin(); enemyIterMove != m_vecEnemy.end(); enemyIterMove++)
    {
        enemyIterMove->Move();
    }

    m_player.IsInsideWindow(false);
}

void MainGame::Render(HDC hdc)
{
    DrawRect(hdc, m_player.GetBodyRect());
    for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end(); iter++)
    {
        DrawRect(hdc, iter->GetBodyRect());
        FillRect(hdc, iter->GetBodyRect(), iter->m_bBrush);
    }

    for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); iter++)
    {
        DrawRect(hdc, iter->GetBodyRect());
        FillRect(hdc, iter->GetBodyRect(), iter->m_bBrush);
    }
}

void MainGame::Setup()
{
    m_isPlaying = false;
    PlayerSetup();
    EnemySetup(MAX_ENEMY);
    m_brushBullet = CreateSolidBrush(RGB(100, 0, 0));
}

void MainGame::PlayerSetup()
{
    POINT ptPlayerPos;
    ptPlayerPos.x = (int)(W_WIDTH * 0.5);
    ptPlayerPos.y = W_HEIGHT - (int)(PLAYER_SIZE * 1.5);

    POINT ptPlayerSize = { PLAYER_SIZE, PLAYER_SIZE };
    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
    m_player.SetBodyRect(ptPlayerPos, ptPlayerSize);
    m_player.SetBrush(brush);
    m_player.SetLifeCount(1);
    m_player.m_playerSpeed = 5;
}

void MainGame::EnemySetup(int EnemyCount)
{
    m_isEnemyArriveWall = false;
    if (EnemyCount > MAX_ENEMY)
    {
        EnemyCount = MAX_ENEMY;
    }

    for (int colIdx = 0; colIdx < ENEMY_COL; colIdx++)
    {
        for (int rowIdx = 0; rowIdx < ENEMY_ROW; rowIdx++)
        {
            Enemy tempEnemy;
            tempEnemy.SetBodyRect(POINT{ ENEMY_SIZE + colIdx * ENEMY_SIZE * 3, ENEMY_SIZE + rowIdx * ENEMY_SIZE * 3 }, POINT{ ENEMY_SIZE, ENEMY_SIZE });
            HBRUSH enemyBrush;
            enemyBrush = CreateSolidBrush(RGB(rowIdx * 20, colIdx * 10, 50));
            tempEnemy.SetBrush(enemyBrush);
            tempEnemy.SetLifeCount(1);
            tempEnemy.SetMoveDir(POINT{ ENEMY_SPEED, 0 });
            m_vecEnemy.push_back(tempEnemy);
        }
    }
}

void MainGame::PlayerControl()
{
    POINT pt;
    pt.x = 0;
    pt.y = 0;
    if (g_pKeyManager->isStayKeyDown('A'))
    {
        //  Move Left
        pt.x = -m_player.m_playerSpeed;
        m_player.SetMoveDir(pt);
    }
    else if (g_pKeyManager->isStayKeyDown('D'))
    {
        //  Move right
        pt.x = m_player.m_playerSpeed;
        m_player.SetMoveDir(pt);
    }
    else
    {
        m_player.IsInsideWindow(true);
    }

    if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
    {
        Bullet shotBullet = m_player.Shot(BULLET_SPEED, m_brushBullet);
        m_vecBullet.push_back(shotBullet);
    }

    if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
    {
        m_isPlaying = !m_isPlaying;
    }
}

void MainGame::DrawRect(HDC hdc, RECT * Rect)
{
    Rectangle(hdc, Rect->left, Rect->top, Rect->right, Rect->bottom);
}
