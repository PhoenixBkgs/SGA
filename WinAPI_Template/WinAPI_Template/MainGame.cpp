#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
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
    GameNode::Update();
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
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

    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        MouseLock();
    }

    if (g_pKeyManager->isStayKeyDown(VK_CONTROL))
    {
        if (g_pKeyManager->isOnceKeyDown(VK_MENU))
        {
            MouseUnlock();
        }
    }

    UnitSpeed speed = { 0.0f, 0.0f };
    if (g_pKeyManager->isStayKeyDown(VK_UP))
    {
        speed.y = -5.0f;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
    {
        speed.y = 5.0f;
    }
    if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        speed.x = -5.0f;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        speed.x = 5.0f;
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
