#include "stdafx.h"
#include "ClearScene.h"

ClearScene::ClearScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


ClearScene::~ClearScene()
{
}

void ClearScene::Update()
{
}

void ClearScene::Render()
{
}

void ClearScene::Setup()
{
}

void ClearScene::LoadImageResources()
{
}

void ClearScene::DeleteScene()
{
}
