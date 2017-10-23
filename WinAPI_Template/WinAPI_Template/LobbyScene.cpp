#include "stdafx.h"
#include "LobbyScene.h"

LobbyScene::LobbyScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


LobbyScene::~LobbyScene()
{
}

void LobbyScene::Update()
{
}

void LobbyScene::Render()
{
}

void LobbyScene::Setup()
{
}

void LobbyScene::LoadImageResources()
{
}

void LobbyScene::DeleteScene()
{
}
