#include "stdafx.h"
#include "GameoverScene.h"

GameoverScene::GameoverScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


GameoverScene::~GameoverScene()
{
}

void GameoverScene::Update()
{
}

void GameoverScene::Render(HDC hdc)
{
}

void GameoverScene::Setup()
{
}

void GameoverScene::LoadImageResources()
{
}

void GameoverScene::DeleteScene()
{
}