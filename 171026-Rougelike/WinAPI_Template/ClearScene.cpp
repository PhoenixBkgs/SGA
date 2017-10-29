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
    RECT rt = { 0, 200, W_WIDTH, 400 };
    g_pDrawHelper->m_textBoxInfo.FontColor = { 0, 0, 0, 255 };
    g_pDrawHelper->DrawTextBox(g_hDC, rt, "CLEAR");
    rt = { 0, 400, W_WIDTH, 500 };
    char result[128];
    sprintf(result, "%d", m_nGameTimer);
    g_pDrawHelper->DrawTextBox(g_hDC, rt, result);
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
