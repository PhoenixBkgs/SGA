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
    GameNode::Update();
    m_player.Move();
    for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end();)
    {
        iter->Move();
        for (auto iter2 = m_vecEnemy.begin(); iter2 != m_vecEnemy.end();)
        {
            RECT tRt1 = *iter->GetBodyRect();
            RECT tRt2 = *iter2->GetBodyRect();

            if (m_map.IsCollision(&tRt1, &tRt2))
            {
                iter->m_isHit = true;
                iter2 = m_vecEnemy.erase(iter2);
                break;
            }
            else
            {
                iter2++;
            }
        }

        if (m_map.IsBulletArrive(iter->GetBodyRect()) ||
            iter->m_isHit)
        {
            //  BULLET END
            iter = m_vecBullet.erase(iter);
        }
        else
        {
            iter++;
        }
    }

    PlayGame();
    m_player.MoveRestrictor(false);
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
    if (EnemyCount > MAX_ENEMY)
    {
        EnemyCount = MAX_ENEMY;
    }

    for (int colIdx = 0; colIdx < ENEMY_COL; colIdx++)
    {
        for (int rowIdx = 0; rowIdx < ENEMY_ROW; rowIdx++)
        {
            Enemy tempEnemy;
            tempEnemy.SetBodyRect(POINT{ colIdx * ENEMY_SIZE * 3, rowIdx * ENEMY_SIZE * 3 }, POINT{ ENEMY_SIZE, ENEMY_SIZE });
            HBRUSH enemyBrush;
            enemyBrush = CreateSolidBrush(RGB(rowIdx * 20, colIdx * 10, 50));
            tempEnemy.SetBrush(enemyBrush);
            tempEnemy.SetLifeCount(1);
            tempEnemy.SetMoveDir(POINT{ 0, 0 });
            m_vecEnemy.push_back(tempEnemy);
        }
    }
}

void MainGame::PlayGame()
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
        m_player.MoveRestrictor(true);
    }

    if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
    {
        Bullet shotBullet = m_player.Shot(BULLET_SPEED, m_brushBullet);
        m_vecBullet.push_back(shotBullet);
    }
}

void MainGame::DrawRect(HDC hdc, RECT * Rect)
{
    Rectangle(hdc, Rect->left, Rect->top, Rect->right, Rect->bottom);
}
