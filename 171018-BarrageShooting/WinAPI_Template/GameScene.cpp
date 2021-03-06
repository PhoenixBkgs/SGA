#include "stdafx.h"
#include "GameScene.h"

#include "MapObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "SpritesObject.h"

GameScene::GameScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
}


GameScene::~GameScene()
{
    SAFE_DELETE(m_pMap);
    SAFE_DELETE(m_pEnemy);
    SAFE_DELETE(m_pPlayer);
}

void GameScene::SetPlayerImg(string szString)
{
    if (szString != "")
    {
        m_pPlayer->SetBodyImg(g_pImgManager->FindImage(szString));
        m_pPlayer->SetupForSprites(1, 3);
    }
}

void GameScene::Update()
{
    m_nScore = m_pPlayer->GetScore();

    if (m_pEnemy->GetHp() < 0.0f)
    {
        *m_currGameState = GAME_CLEAR;
    }

    if (m_pPlayer->GetHp() < 0.0f)
    {
        *m_currGameState = GAME_OVER;
    }
    m_pPlayer->Update();
    m_pEnemy->Update();
    m_pMap->Update();

    //  Bullets move
    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
    {
        iter->Update();
    }

    //  Items move
    for (auto iter = m_vecItems.begin(); iter != m_vecItems.end(); iter++)
    {
        iter->Update();
        if (iter->IsAlive() == true)
        {
            if (g_pPhxsHelper->IsCollision(m_pPlayer, iter._Ptr))
            {
                m_pPlayer->SumScore(iter->GetScore());
                iter->SetDead();
            }
        }
    }

    //  Bullets collision
    m_iterBullets = m_vecBullets.begin();
    while (m_iterBullets != m_vecBullets.end())
    {
        if (m_iterBullets->IsAlive() == true)
        {
            //  check collision player-bullet and enemy
            if (m_iterBullets->GetTagName() == "player-bullet" &&
                g_pPhxsHelper->IsCollision(m_iterBullets._Ptr, m_pEnemy))
            {
                if (m_pEnemy->IsImmortal())
                {

                }
                else
                {
                    m_pEnemy->SumHp(m_iterBullets->GetDamage());
                    double genRand = (double)(rand() % 10000) * 0.01f;
                    if (genRand > 75.0f)
                    {
                        GenItem();
                    }
                }
                m_iterBullets->SetDead();
            }

            //  check collision enemy-bullet and player
            if (m_iterBullets->GetTagName() == "enemy-bullet" &&
                g_pPhxsHelper->IsCollision(m_iterBullets._Ptr, m_pPlayer))
            {
                if (m_pPlayer->IsImmortal())
                {

                }
                else
                {
                    m_pPlayer->SumHp(m_iterBullets->GetDamage());
                }
                m_iterBullets->SetDead();
            }
        }

        m_iterBullets++;
    }

    //  Bullets expire
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

    //  Items expire
    for (auto iter = m_vecItems.begin(); iter != m_vecItems.end();)
    {
        if (iter->IsAlive() == false)
        {
            iter = m_vecItems.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

void GameScene::Render()
{
    m_pMap->Render();
    m_pEnemy->Render();
    m_pPlayer->Render();

    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
    {
        iter->Render();
    }

    for (auto iter = m_vecItems.begin(); iter != m_vecItems.end(); iter++)
    {
        iter->Render();
    }

    m_scoreBoard->GetSpritesImg()->SpritesRender(g_hDC, m_scoreBoard->GetPos(), m_scoreBoard->GetSize(), m_nScore);
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "bullet count : %d // score : %d", (int)m_vecBullets.size(), m_nScore);
    TextOut(g_hDC, 0, 30, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG

}

void GameScene::Setup()
{
    m_nScore = 0;

    //  PLAYER
    m_pPlayer = new Player("player");
    m_pPlayer->SetBodyImg(g_pImgManager->FindImage("player"));
    m_pPlayer->SetupForSprites(1, 3);
    m_pPlayer->Setup(UnitPos{ PLAYER_INIT_POS_X, PLAYER_INIT_POS_Y }, UnitSize{ PLAYER_WIDTH, PLAYER_HEIGHT });
    m_pPlayer->SetHBoxMargin(RectMargin{ 25, 15, 25, 35 });
    m_pPlayer->LockInWnd();
    m_pPlayer->SetLife(10);
    m_pPlayer->SetupForProgressBar();
    m_pPlayer->SetScore(0);

    //  ENEMY
    m_pEnemy = new Enemy("enemy");
    m_pEnemy->SetBodyImg(g_pImgManager->FindImage("enemy"));
    m_pEnemy->SetupForSprites(1, 1);
    m_pEnemy->Setup(UnitPos{ BOSS_INIT_POS_X, BOSS_INIT_POS_Y }, UnitSize{ BOSS_WIDTH, BOSS_HEIGHT });
    m_pEnemy->SetHBoxMargin(RectMargin{ 100, 15, 100, 100 });
    m_pEnemy->LockInWnd();
    m_pEnemy->SetLife(10);
    m_pEnemy->SetupForProgressBar();

    //  MUTUAL REF
    m_pPlayer->SetEnemy(m_pEnemy);
    m_pPlayer->SetBullet(&m_vecBullets);
    m_pEnemy->SetPlayer(m_pPlayer);
    m_pEnemy->SetBullet(&m_vecBullets);

    //  MAP
    m_pMap = new MapObject();
    m_pMap->SetBodyImg(g_pImgManager->FindImage("map"));
    m_pMap->SetBodyPos(g_pGeoHelper->GetCenterPointWindow());
    m_pMap->SetBodySize(UnitSize{ m_pMap->GetBodyImg()->GetWidth(), m_pMap->GetBodyImg()->GetHeight() });
    m_pMap->Setup(m_pMap->GetPos(), m_pMap->GetSize());
    m_pMap->SetMapArea(g_pDrawHelper->MakeRect(m_pMap->GetPos(), m_pMap->GetSize()));
    m_pPlayer->SetLockArea(m_pMap->GetMapArea());
    m_pEnemy->SetLockArea(m_pMap->GetMapArea());

    //  SCORE BOARD
    m_scoreBoard = new SpritesObject;
    m_scoreBoard->SetBodyImg(g_pImgManager->FindImage("number"));
    m_scoreBoard->SetupForSprites(10, 1);
    m_scoreBoard->SetBodyPos(UnitPos{ W_WIDTH - 25.0f, 25.0f });
    m_scoreBoard->SetBodySize(UnitSize{ 50, 50 });
    m_scoreBoard->SetBodyRect(g_pDrawHelper->MakeRect(m_scoreBoard->GetPos(), m_scoreBoard->GetSize()));
    m_scoreBoard->SetHBoxMargin(RectMargin{ 0, 0, 0, 0 });
}

void GameScene::LoadImageResources()
{
    //  GAME UNIT
    g_pImgManager->AddImage("player", "images/sprites-player.bmp", 60, 210);    //  60 x 70px _ 1 x 3
    g_pImgManager->AddImage("player2", "images/sprites-player-2.bmp", 60, 210);    //  60 x 70px _ 1 x 3
    g_pImgManager->AddImage("bullet", "images/sprites-bullet.bmp", 64, 64);     //  32 x 32px _ 2 x 2
    g_pImgManager->AddImage("enemy", "images/sprites-boss.bmp", 480, 351);     //  480 x 351px _ 1 x 1
    g_pImgManager->AddImage("map", "images/img-map.bmp", 512, 1024);         //  512 x 1024px _ 1 x 1
    g_pImgManager->AddImage("item", "images/img-item.bmp", 100, 100);   //  100 x 100px _ 1 x 1
    g_pImgManager->AddImage("number", "images/sprites-number.bmp", 500, 50);    //  50 x 50px _ 10 x 1
}

void GameScene::DeleteScene()
{
}

void GameScene::GenItem()
{
    Item genItem;
    m_vecItems.push_back(genItem.GenItem(m_pEnemy->GetPos(), UnitSize{ 100, 100 }));
}
