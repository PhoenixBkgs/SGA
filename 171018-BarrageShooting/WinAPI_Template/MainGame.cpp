#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_currGameState = GAME_LOADING;
    LoadAllResources();
    Start();
}


MainGame::~MainGame()
{
    g_pImgManager->DeleteImageAll();
    g_pScnManager->DeleteAllScene();
    g_pTimerManager->DeleteTimerAll();

    ReleaseAllScene();
}

void MainGame::Start()
{
    m_szPlayerSelect = "";
    m_nScore = 0;
    SetupScene();
}

void MainGame::Update()
{
    SystemController();
    switch (m_currGameState)
    {
    case GAME_LOADING:
        g_pScnManager->Update("loading");
        break;
    case GAME_READY:
        g_pScnManager->Update("ready");
        break;
    case GAME_LOBBY:
        g_pScnManager->Update("lobby");
        m_szPlayerSelect = m_lobbyScn->GetPlayerSelect();
        m_gameScn->SetPlayerImg(m_szPlayerSelect);
        break;
    case GAME_PLAYING:
        g_pScnManager->Update("game");
        m_nScore = m_gameScn->GetScore();
        break;
    case GAME_PAUSE:
        break;
    case GAME_CLEAR:
        m_clearScn->SetScore(m_nScore);
        g_pScnManager->Update("clear");
        break;
    case GAME_OVER:
        g_pScnManager->Update("gameover");
        break;
    default:
        break;
    }
    GameNode::Update();     //  InvalidRect()
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
    switch (m_currGameState)
    {
    case GAME_LOADING:
        g_pScnManager->Render("loading");
        break;
    case GAME_READY:
        g_pScnManager->Render("ready");
        break;
    case GAME_LOBBY:
        g_pScnManager->Render("lobby");
        break;
    case GAME_PLAYING:
    case GAME_PAUSE:
        g_pScnManager->Render("game");
        if (m_currGameState == GAME_PAUSE)
        {
            g_pScnManager->Render("pause");
        }
        break;
    case GAME_CLEAR:
        g_pScnManager->Render("game");
        g_pScnManager->Render("clear");
        break;
    case GAME_OVER:
        g_pScnManager->Render("game");
        g_pScnManager->Render("gameover");
        break;
    default:
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
    //  HUD
    g_pImgManager->AddImage("hp-frame", "images/sprites-health-frame.bmp", 480, 46);    //  480 x 46px _ 1 x 2
    g_pImgManager->AddImage("hp-bar",   "images/sprites-health-bar.bmp", 456, 96);      //  456 x 96px _ 1 x 8
    g_pImgManager->AddImage("hp-bar-2", "images/sprites-health-bar-2.bmp", 456, 96);      //  456 x 96px _ 1 x 8
}

void MainGame::LoadSoundResources()
{
    
}

void MainGame::SetupScene()
{
    //  Loading scene
    m_loadingScn = new LoadingScene(&m_currGameState);
    g_pScnManager->AddGameObjToScn("loading", m_loadingScn);

    //  Ready scene
    m_readyScn = new SplashScene(&m_currGameState);
    g_pScnManager->AddGameObjToScn("ready", m_readyScn);
    
    //  Lobby scene
    m_lobbyScn = new LobbyScene(&m_currGameState);
    m_lobbyScn->SetPlayerSelect(m_szPlayerSelect);
    g_pScnManager->AddGameObjToScn("lobby", m_lobbyScn);

    //  Menu scene
    m_menuScn = new MenuScene(&m_currGameState);
    g_pScnManager->AddGameObjToScn("pause", m_menuScn);

    //  Game scene
    m_gameScn = new GameScene(&m_currGameState);
    m_gameScn->SetPlayerSelect(m_szPlayerSelect);
    m_gameScn->Setup();
    g_pScnManager->AddGameObjToScn("game", m_gameScn);
    
    //  Clear scene
    m_clearScn = new ClearScene(&m_currGameState);
    g_pScnManager->AddGameObjToScn("clear", m_clearScn);

    //  Game over scene
    m_gameoverScn = new GameoverScene(&m_currGameState);
    g_pScnManager->AddGameObjToScn("gameover", m_gameoverScn);
}

void MainGame::ReleaseAllScene()
{
    SAFE_DELETE(m_menuScn);
    SAFE_DELETE(m_readyScn);
    SAFE_DELETE(m_loadingScn);
    SAFE_DELETE(m_gameScn);
}

void MainGame::SystemController()
{
    if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
    {
        PostQuitMessage(0);
    }

    if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
    {
        switch (m_currGameState)
        {
        case GAME_READY:
            m_currGameState = GAME_LOBBY;
            break;
        case GAME_LOBBY:
            break;
        case GAME_PLAYING:
            m_currGameState = GAME_PAUSE;
            break;
        case GAME_PAUSE:
            m_currGameState = GAME_PLAYING;
            break;
        case GAME_CLEAR:
            break;
        case GAME_OVER:
            break;
        default:
            break;
        }
    }
}
