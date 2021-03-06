﻿#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


GameScene::~GameScene()
{
}

void GameScene::Update()
{
}

void GameScene::Render(HDC hdc)
{
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "");
    TextOut(hdc, 0, 30, infoMsg, (int)strlen(infoMsg));
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