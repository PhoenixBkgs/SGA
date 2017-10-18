#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    LoadAllResources();
    Start();
}


MainGame::~MainGame()
{
}

void MainGame::Start()
{
    m_currGameState = GAME_READY;
    m_count = 0;
    m_pPlayer = new Player("player");
    m_pPlayer->SetHBoxMargin(RectMargin{ 15, 15, 15, 15 });
    m_pPlayer->Setup(UnitPos{ PLAYER_INIT_POS_X, PLAYER_INIT_POS_Y }, UnitSize{ PLAYER_WIDTH, PLAYER_HEIGHT });
    m_pPlayer->LockInWnd();
    m_pPlayer->SetupForSprites(1, 3);
    m_pPlayer->SetSpritesImg(g_pImgManager->FindImage("player"));
    m_pPlayer->SetLife(10);

    m_pEnemy = new Enemy("enemy");
    m_pEnemy->SetHBoxMargin(RectMargin{ 15, 15, 15, 15 });
    m_pEnemy->Setup(UnitPos{ BOSS_INIT_POS_X, BOSS_INIT_POS_Y }, UnitSize{ BOSS_WIDTH, BOSS_HEIGHT });
    m_pEnemy->SetupForSprites(1, 1);
    m_pEnemy->LockInWnd();
    m_pEnemy->SetSpritesImg(g_pImgManager->FindImage("enemy"));
    m_pEnemy->SetLife(10);

    //  MUTUAL REF
    m_pPlayer->SetEnemy(m_pEnemy);
    m_pEnemy->SetPlayer(m_pPlayer);
    
    g_pScnManager->AddGameObject("game", m_pPlayer);
    g_pScnManager->AddGameObject("game", m_pEnemy);
}

void MainGame::Update()
{
    SystemController();
    switch (m_currGameState)
    {
    case GAME_READY:
        break;
    case GAME_PLAYING:
        PlayerController();
        /*
        m_pPlayer->Update();
        m_pEnemy->Update();
        g_pScnManager->Update("player");
        g_pScnManager->Update("enemy");
        */
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
        /*
        g_pScnManager->Render("player");
        g_pScnManager->Render("enemy");
        */
        g_pScnManager->Render("game");
        break;
    case GAME_CLEAR:
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
    g_pImgManager->AddImage("player", "images/sprites-player.bmp", 60, 210);    //  60 x 70px _ 1 x 3
    g_pImgManager->AddImage("bullet", "images/sprites-bullet.bmp", 64, 64);     //  32 x 32px _ 2 x 2
    g_pImgManager->AddImage("enemy",  "images/sprites-boss.bmp", 480, 351);     //  480 x 351px _ 1 x 1
}

void MainGame::LoadSoundResources()
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
    if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        dPlayerSpd.x = PLAYER_SPEED;
        m_pPlayer->SetFrameY(2);
    }
    if (g_pKeyManager->isStayKeyDown(VK_UP))
    {
        dPlayerSpd.y = -PLAYER_SPEED;
    }
    if (g_pKeyManager->isStayKeyDown(VK_DOWN))
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
