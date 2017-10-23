#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
}


GameScene::~GameScene()
{
}

void GameScene::Update()
{
}

void GameScene::Render()
{
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "");
    TextOut(g_hDC, 0, 30, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG

}

void GameScene::Setup()
{
}

void GameScene::LoadImageResources()
{
}

void GameScene::DeleteScene()
{
}