#include "stdafx.h"
#include "GameScene.h"

#include "MapObject.h"
#include "Player.h"
#include "Enemy.h"

GameScene::GameScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
    AddComponentsToScene();
}


GameScene::~GameScene()
{
    SAFE_DELETE(m_pMap);
    SAFE_DELETE(m_pEnemy);
    SAFE_DELETE(m_pPlayer);
}

void GameScene::Update()
{
    if (m_pEnemy->GetHp() < 0.0f)
    {
        *m_currGameState = GAME_CLEAR;
    }
}

void GameScene::Setup()
{
    //  PLAYER
    m_pPlayer = new Player("player");
    m_pPlayer->SetHBoxMargin(RectMargin{ 25, 15, 25, 35 });
    m_pPlayer->Setup(UnitPos{ PLAYER_INIT_POS_X, PLAYER_INIT_POS_Y }, UnitSize{ PLAYER_WIDTH, PLAYER_HEIGHT });
    m_pPlayer->LockInWnd();
    m_pPlayer->SetupForSprites(1, 3);
    m_pPlayer->SetSpritesImg(g_pImgManager->FindImage("player"));
    m_pPlayer->SetLife(10);
    m_pPlayer->SetupForProgressBar();

    //  ENEMY
    m_pEnemy = new Enemy("enemy");
    m_pEnemy->SetHBoxMargin(RectMargin{ 100, 15, 100, 100 });
    m_pEnemy->Setup(UnitPos{ BOSS_INIT_POS_X, BOSS_INIT_POS_Y }, UnitSize{ BOSS_WIDTH, BOSS_HEIGHT });
    m_pEnemy->SetupForSprites(1, 1);
    m_pEnemy->LockInWnd();
    m_pEnemy->SetSpritesImg(g_pImgManager->FindImage("enemy"));
    m_pEnemy->SetLife(10);
    m_pEnemy->SetupForProgressBar();

    //  MUTUAL REF
    m_pPlayer->SetEnemy(m_pEnemy);
    m_pEnemy->SetPlayer(m_pPlayer);

    //  MAP
    m_pMap = new MapObject();
    m_pMap->SetBodyImg(g_pImgManager->FindImage("map"));
    m_pMap->SetBodyPos(g_pGeoHelper->GetCenterPointWindow());
    m_pMap->SetBodySize(UnitSize{ m_pMap->GetBodyImg()->GetWidth(), m_pMap->GetBodyImg()->GetHeight() });
    m_pMap->Setup(m_pMap->GetPos(), m_pMap->GetSize());
    m_pMap->SetMapArea(g_pDrawHelper->MakeRect(m_pMap->GetPos(), m_pMap->GetSize()));
    m_pPlayer->SetLockArea(m_pMap->GetMapArea());
    m_pEnemy->SetLockArea(m_pMap->GetMapArea());
}

void GameScene::LoadImageResources()
{
    //  GAME UNIT
    g_pImgManager->AddImage("player", "images/sprites-player.bmp", 60, 210);    //  60 x 70px _ 1 x 3
    g_pImgManager->AddImage("bullet", "images/sprites-bullet.bmp", 64, 64);     //  32 x 32px _ 2 x 2
    g_pImgManager->AddImage("enemy", "images/sprites-boss.bmp", 480, 351);     //  480 x 351px _ 1 x 1
    g_pImgManager->AddImage("map", "images/img-map.bmp", 512, 1024);         //  512 x 1024px _ 1 x 1
}

void GameScene::AddComponentsToScene()
{
    g_pScnManager->AddGameObjToScn("game", m_pMap);
    g_pScnManager->AddGameObjToScn("game", m_pEnemy);
    g_pScnManager->AddGameObjToScn("game", m_pPlayer);
}

void GameScene::DeleteScene()
{
}
