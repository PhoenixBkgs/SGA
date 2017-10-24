#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


GameScene::~GameScene()
{
    SAFE_DELETE(m_pPlayer);
}

void GameScene::Update()
{
    m_pPlayer->Update();
}

void GameScene::Render()
{
    m_pPlayer->Render();
#ifdef _DEBUG
    /*
    char infoMsg[128];
    sprintf_s(infoMsg, "");
    TextOut(g_hDC, 0, 30, infoMsg, (int)strlen(infoMsg));
    */
#endif // _DEBUG
}

void GameScene::Setup()
{
    m_pPlayer = new Player;
    m_pPlayer->SetBodyImg(g_pImgManager->FindImage("player"));
    m_pPlayer->SetBodySize({ 128, 128 });
    m_pPlayer->SetupForSprites(6, 3);
}

void GameScene::LoadImageResources()
{
    g_pImgManager->AddImage("player", "images/player-sprites-sheet.bmp", 192, 96);  //  32 x 32px _ 6 x 3
}

void GameScene::DeleteScene()
{
}