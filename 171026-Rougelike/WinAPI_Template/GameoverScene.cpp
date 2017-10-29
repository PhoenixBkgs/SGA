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

void GameoverScene::Render()
{
    RECT rt = { 0, 200, W_WIDTH, 400 };
    g_pDrawHelper->m_textBoxInfo.FontColor = { 0, 0, 0, 255 };
    g_pDrawHelper->DrawTextBox(g_hDC, rt, "GAME OVER");
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