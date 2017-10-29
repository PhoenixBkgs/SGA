#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_gameState = GAME_READY;
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
    m_scnLoading = new LoadingScene(&m_gameState);
    g_pScnManager->AddGameObjToScn("loading", m_scnLoading);

    m_mapGen.Setup("map.txt");
    m_nMapSize = m_mapGen.GetMapSize();
    vector<SpritesObject>  genGameObjs = m_mapGen.GetGameObjects();
    m_pImgMinimap = g_pImgManager->AddImage("minimap"
                                        , m_nMapSize.w * 0.10000f
                                        , m_nMapSize.h * 0.1000f);
    m_scnGame = new GameScene(&m_gameState);
    m_scnGame->SetGameObjs(genGameObjs);
    m_scnGame->SetMapSize(m_nMapSize);
    m_scnGame->Setup();
    g_pScnManager->AddGameObjToScn("game", m_scnGame);

    m_scnClear = new ClearScene(&m_gameState);
    m_scnClear->Setup();
    g_pScnManager->AddGameObjToScn("clear", m_scnClear);

    m_scnOver = new GameoverScene(&m_gameState);
    m_scnOver->Setup();
    g_pScnManager->AddGameObjToScn("over", m_scnOver);
}

void MainGame::Update()
{
    SystemController();
    switch (m_gameState)
    {
    case GAME_READY:
        g_pScnManager->Update("loading");
        break;
    case GAME_PLAYING:
        g_pScnManager->Update("game");
        break;
    case GAME_PAUSE:
        break;
    case GAME_CLEAR:
        m_scnClear->SetGameTimer(m_scnGame->GetGameTimer());
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
        g_pScnManager->Render("loading");
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
        g_pScnManager->Render("clear");
        break;
    case GAME_OVER:
        g_pScnManager->Render("over");
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
