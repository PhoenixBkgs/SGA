#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    LoadAllResources();
    Start();
}


MainGame::~MainGame()
{
    g_pImgManager->DeleteImageAll();
    g_pScnManager->DeleteAllScene();
    g_pTimerManager->DeleteTimerAll();
}

void MainGame::Start()
{
    m_currGameState = GAME_READY;
    m_count = 0;
    SetupScene();
    SetupClearScene();
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
    //  READY SCREEN
    g_pImgManager->AddImage("splash-bg", "images/img-splash-bg.bmp", 640, 1023);
    g_pImgManager->AddImage("splash-deco", "images/img-splash-deco.bmp", 366, 537);
    g_pImgManager->AddImage("title", "images/img-title.bmp", 169, 408);
    g_pImgManager->AddImage("start-button", "images/img-start-button.bmp", 213, 65);

    //  MENU
    g_pImgManager->AddImage("menu", "images/img-menu.bmp", 144, 255);

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
    UnitPos centerPos = g_pGeoHelper->GetCenterPointWindow();

    SpritesObject* bg;
    bg = new SpritesObject;
    bg->Setup(centerPos, { W_WIDTH, W_HEIGHT });
    bg->SetBodyImg(g_pImgManager->FindImage("splash-bg"));
    bg->SetupForSprites(1, 1);

    SpritesObject* bgDeco = new SpritesObject;
    UnitSize bgDecoSize = g_pImgManager->FindImage("splash-deco")->GetSize();
    bgDeco->SetBodyPos({ (double)(W_WIDTH - bgDecoSize.w * 0.5f), centerPos.y * 0.5f });
    bgDeco->SetBodySize(bgDecoSize);
    bgDeco->SetBodyRect(g_pDrawHelper->MakeRect(bgDeco->GetPos(), bgDeco->GetSize()));
    bgDeco->SetBodyImg(g_pImgManager->FindImage("splash-deco"));
    bgDeco->SetupForSprites(1, 1);

    SpritesObject* title = new SpritesObject;
    UnitSize titleSize = g_pImgManager->FindImage("title")->GetSize();
    title->Setup(centerPos, titleSize);
    title->SetBodyImg(g_pImgManager->FindImage("title"));
    title->SetupForSprites(1, 1);

    StartButton* startBtn = new StartButton;
    startBtn->Setup({ centerPos.x, centerPos.y + 400.0f }, { 213, 65 });
    startBtn->SetState(&m_currGameState);
    startBtn->SetBodyImg(g_pImgManager->FindImage("start-button"));
    startBtn->SetupForSprites(1, 1);
    
    g_pScnManager->AddGameObjToScn("ready", bg);
    g_pScnManager->AddGameObjToScn("ready", bgDeco);
    g_pScnManager->AddGameObjToScn("ready", title);
    g_pScnManager->AddGameObjToScn("ready", startBtn);

    SpritesObject* pause = new SpritesObject;
    pause->Setup(centerPos, { W_WIDTH, W_HEIGHT });
    pause->SetBodyImg(g_pImgManager->FindImage("splash-bg"));
    pause->SetupForSprites(1, 1);
    pause->SetAlpha(128.0f);

    SpritesObject* menu = new SpritesObject;
    menu->SetBodyImg(g_pImgManager->FindImage("menu"));
    menu->Setup(centerPos, menu->GetBodyImg()->GetSize());
    menu->SetupForSprites(1, 1);

    g_pScnManager->AddGameObjToScn("pause", pause);
    g_pScnManager->AddGameObjToScn("pause", menu);
}

void MainGame::SetupClearScene()
{
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
