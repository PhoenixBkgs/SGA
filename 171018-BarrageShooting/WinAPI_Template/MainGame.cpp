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
    m_count = 0;
    SetupScene();

    //  PLAYER
    m_pPlayer = new Player("player");
    m_pPlayer->SetHBoxMargin(RectMargin{ 25, 15, 25, 35 });
    m_pPlayer->Setup(UnitPos{ PLAYER_INIT_POS_X, PLAYER_INIT_POS_Y }, UnitSize{ PLAYER_WIDTH, PLAYER_HEIGHT });
    m_pPlayer->LockInWnd();
    m_pPlayer->SetupForSprites(1, 3);
    m_pPlayer->SetSpritesImg(g_pImgManager->FindImage("player"));
    m_pPlayer->SetLife(10);
    m_pPlayer->SetupForProgressBar();

    //  ENEMY
    m_pEnemy = new Enemy("enemy");
    m_pEnemy->SetHBoxMargin(RectMargin{ 100, 15, 100, 100 });
    m_pEnemy->Setup(UnitPos{ BOSS_INIT_POS_X, BOSS_INIT_POS_Y }, UnitSize{ BOSS_WIDTH, BOSS_HEIGHT });
    m_pEnemy->SetupForSprites(1, 1);
    m_pEnemy->LockInWnd();
    m_pEnemy->SetSpritesImg(g_pImgManager->FindImage("enemy"));
    m_pEnemy->SetLife(10);
    m_pEnemy->SetupForProgressBar();

    //  MUTUAL REF
    m_pPlayer->SetEnemy(m_pEnemy);
    m_pEnemy->SetPlayer(m_pPlayer);
    
    //  MAP
    m_pMap = new MapObject();
    m_pMap->SetBodyImg(g_pImgManager->FindImage("map"));
    m_pMap->SetBodyPos(g_pGeoHelper->GetCenterPointWindow());
    m_pMap->SetBodySize(UnitSize{ m_pMap->GetBodyImg()->GetWidth(), m_pMap->GetBodyImg()->GetHeight() });
    m_pMap->Setup(m_pMap->GetPos(), m_pMap->GetSize());
    m_pMap->SetMapArea(g_pDrawHelper->MakeRect(m_pMap->GetPos(), m_pMap->GetSize()));
    m_pPlayer->SetLockArea(m_pMap->GetMapArea());
    m_pEnemy->SetLockArea(m_pMap->GetMapArea());

    g_pScnManager->AddGameObjToScn("game", m_pMap);
    g_pScnManager->AddGameObjToScn("game", m_pEnemy);
    g_pScnManager->AddGameObjToScn("game", m_pPlayer);
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
    case GAME_PLAYING:
        PlayerController();
        g_pScnManager->Update("game");
        break;
    case GAME_PAUSE:
        break;
    case GAME_CLEAR:
        break;
    case GAME_OVER:
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
    case GAME_PLAYING:
    case GAME_PAUSE:
        g_pScnManager->Render("game");
        if (m_pEnemy->GetHp() < 0.0f)
        {
            m_currGameState = GAME_CLEAR;
        }
        if (m_currGameState == GAME_PAUSE)
        {
            g_pScnManager->Render("pause");
        }
        break;
    case GAME_CLEAR:
        g_pScnManager->Render("clear");
        break;
    case GAME_OVER:
        break;
    default:
        break;
    }
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "player pos x : %f  /  y : %f", m_pPlayer->GetPos().x, m_pPlayer->GetPos().y);
    TextOut(g_hDC, 0, 0, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
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
    g_pImgManager->AddImage("gameover", "images/img-gameover.bmp", 439, 268);            //  439 x 268px _ 1 x 4

    //  GAME UNIT
    g_pImgManager->AddImage("player", "images/sprites-player.bmp", 60, 210);    //  60 x 70px _ 1 x 3
    g_pImgManager->AddImage("bullet", "images/sprites-bullet.bmp", 64, 64);     //  32 x 32px _ 2 x 2
    g_pImgManager->AddImage("enemy",  "images/sprites-boss.bmp", 480, 351);     //  480 x 351px _ 1 x 1
    g_pImgManager->AddImage("map",    "images/img-map.bmp", 512, 1024);         //  512 x 1024px _ 1 x 1
}

void MainGame::LoadSoundResources()
{
    
}

void MainGame::SetupScene()
{
    m_loadingScn = new LoadingScene(&m_currGameState);
    m_splashScn = new SplashScene(&m_currGameState);
    m_menuScn = new MenuScene(&m_currGameState);

    g_pScnManager->AddGameObjToScn("loading", m_loadingScn);
}

void MainGame::ReleaseAllScene()
{
    SAFE_DELETE(m_menuScn);
    SAFE_DELETE(m_splashScn);
    SAFE_DELETE(m_loadingScn);
}

void MainGame::PlayerController()
{
    UnitSpeed dPlayerSpd = { 0.0f, 0.0f };
    m_pPlayer->SetFrameY(0);
    if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        dPlayerSpd.x = -PLAYER_SPEED;
        m_pPlayer->SetFrameY(1);
    }
    else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        dPlayerSpd.x = PLAYER_SPEED;
        m_pPlayer->SetFrameY(2);
    }
    if (g_pKeyManager->isStayKeyDown(VK_UP))
    {
        dPlayerSpd.y = -PLAYER_SPEED;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
    {
        dPlayerSpd.y = PLAYER_SPEED;
    }
    m_pPlayer->SetBodySpeed(dPlayerSpd);

    if (g_pKeyManager->isStayKeyDown(VK_SPACE))
    {
        m_pPlayer->Shoot();
    }
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
            m_currGameState = GAME_PLAYING;
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
