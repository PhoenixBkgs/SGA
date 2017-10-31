#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    //  전체 맵 로딩
    m_pWorldMap = g_pImgManager->AddImage("world-map", "images/exia-repair.bmp", 4898, 3265);
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
    m_pWorldMap->ViewportRender(g_hDC, g_rtViewPort);
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

    //  Ctrl + Alt 키 조합으로 마우스 가두기 해제
    if (g_pKeyManager->isStayKeyDown(VK_CONTROL))
    {
        if (g_pKeyManager->isOnceKeyDown(VK_MENU))
        {
            MouseUnlock();
        }
    }

    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        MouseLock();    //  창 내부 클릭 시 마우스 가두기
    }

    if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        g_rtViewPort.left += 10;
        g_rtViewPort.right = g_rtViewPort.left + W_WIDTH;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        g_rtViewPort.left -= 10;
        g_rtViewPort.right = g_rtViewPort.left + W_WIDTH;
    }

    if (g_pKeyManager->isStayKeyDown(VK_UP))
    {
        g_rtViewPort.top -= 10;
        g_rtViewPort.bottom = g_rtViewPort.top + W_HEIGHT;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
    {
        g_rtViewPort.top += 10;
        g_rtViewPort.bottom = g_rtViewPort.top + W_HEIGHT;
    }

    if (g_pKeyManager->isStayKeyDown('W'))
    {
        g_rtViewPort.left -= 1;
        g_rtViewPort.right += 1;
        g_rtViewPort.top -= 1;
        g_rtViewPort.bottom += 1;
    }
    else if (g_pKeyManager->isStayKeyDown('D'))
    {
        g_rtViewPort.left += 1;
        g_rtViewPort.right -= 1;
        g_rtViewPort.top += 1;
        g_rtViewPort.bottom -= 1;
    }
}

void MainGame::MouseLock()
{
    RECT Rt;
    GetWindowRect(g_hWnd, &Rt);
    if (PtInRect(&Rt, g_ptMouse))
        ClipCursor(&Rt);
}

void MainGame::MouseUnlock()
{
    ClipCursor(NULL);
}
