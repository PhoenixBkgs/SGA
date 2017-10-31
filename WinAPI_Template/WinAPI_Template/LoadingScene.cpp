#include "stdafx.h"
#include "LoadingScene.h"


LoadingScene::LoadingScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


LoadingScene::~LoadingScene()
{
}

void LoadingScene::Update()
{
}

void LoadingScene::Render(HDC hdc)
{
}

void LoadingScene::Setup()
{
}

void LoadingScene::LoadImageResources()
{
}

void LoadingScene::DeleteScene()
{
}
