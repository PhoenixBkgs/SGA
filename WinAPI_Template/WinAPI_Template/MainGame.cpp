#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_gameState = GAME_PLAYING;
    MouseLock();
    LoadAllResources();
    Start();
}


MainGame::~MainGame()
{
}

void MainGame::Start()
{
}

void MainGame::Update()
{
    SystemController();
    switch (m_gameState)
    {
    case GAME_LOADING:
        break;
    case GAME_READY:
        break;
    case GAME_PLAYING:
        break;
    case GAME_PAUSE:
        break;
    case GAME_CLEAR:
        break;
    case GAME_OVER:
        break;
    }

    GameNode::Update();
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, BLACKNESS);
    switch (m_gameState)
    {
    case GAME_READY:
        break;
    case GAME_PLAYING:
        break;
    case GAME_PAUSE:
        break;
    case GAME_CLEAR:
        break;
    case GAME_OVER:
        break;
    }
}

void MainGame::Reset()
{
}

void MainGame::LoadAllResources()
{
    LoadImageResources();
    LoadSoundResources();
}

void MainGame::LoadImageResources()
{
}

void MainGame::LoadSoundResources()
{
}

void MainGame::SystemController()
{
    if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
    {
        PostQuitMessage(0);
    }

    if (g_pKeyManager->isStayKeyDown(VK_CONTROL))
    {
        if (g_pKeyManager->isOnceKeyDown(VK_MENU))
        {
            MouseUnlock();
        }
    }
    RECT Rt;
    GetWindowRect(g_hWnd, &Rt);
    if (PtInRect(&Rt, g_ptMouse))
    {
        if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
        {
            MouseLock();
        }
    }
}

void MainGame::MouseLock()
{
    RECT Rt;
    GetWindowRect(g_hWnd, &Rt);
    ClipCursor(&Rt);
}

void MainGame::MouseUnlock()
{
    ClipCursor(NULL);
}
