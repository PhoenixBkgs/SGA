#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_gameState = GAME_PLAYING;
	m_brush = CreateSolidBrush(RGB(255, 0, 255));
    MouseLock();
    LoadAllResources();
    Start();
}


MainGame::~MainGame()
{
    SAFE_DELETE(m_scnGame);
}

void MainGame::Start()
{
    m_mapGen.Setup("map.txt");
    m_nMapSize = m_mapGen.GetMapSize();
    m_pImgMinimap = g_pImgManager->AddImage("minimap"
                                        , m_nMapSize.w * 0.10000f
                                        , m_nMapSize.h * 0.1000f);
    m_scnGame = new GameScene(&m_gameState);
    m_scnGame->SetMapSize(m_nMapSize);
    m_scnGame->Setup();
    g_pScnManager->AddGameObjToScn("game", m_scnGame);
}

void MainGame::Update()
{
    SystemController();
    switch (m_gameState)
    {
    case GAME_READY:
        break;
    case GAME_PLAYING:
        g_pScnManager->Update("game");
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
	{
		PatBlt(m_pImgMinimap->GetMemDC(), 0, 0, m_pImgMinimap->GetWidth(), m_pImgMinimap->GetHeight(), BLACKNESS);
        g_pScnManager->Render("game");
		m_pImgMinimap->Render(g_hDC
			, (int)(W_WIDTH - 500), 0
			, 500, 150
			, 0, 0
			, m_pImgMinimap->GetWidth(), m_pImgMinimap->GetHeight()
			, 255);
        break;
	}
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
