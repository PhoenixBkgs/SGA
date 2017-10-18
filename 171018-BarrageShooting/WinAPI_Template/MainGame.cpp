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
    m_count = 0;
    m_pPlayer = new Player("player");
    m_pPlayer->SetHBoxMargin(RectMargin{ 15, 15, 15, 15 });
    m_pPlayer->Setup(UnitPos{ PLAYER_INIT_POS_X, PLAYER_INIT_POS_Y }, UnitSize{ PLAYER_WIDTH, PLAYER_HEIGHT });
    m_pPlayer->SpritesSetup(1, 3);

    m_pEnemy = new Enemy("enemy");
    m_pEnemy->SetHBoxMargin(RectMargin{ 15, 15, 15, 15 });
    m_pEnemy->Setup(UnitPos{ BOSS_INIT_POS_X, BOSS_INIT_POS_Y }, UnitSize{ BOSS_WIDTH, BOSS_HEIGHT });
    m_pEnemy->SpritesSetup(1, 1);
}

void MainGame::Update()
{
    PlayerController();
    SystemController();
    if (m_bIsPlaying)
    {
        return;
    }
    m_pPlayer->Update();
    m_pEnemy->Update();
    m_count++;
    if (m_count > 5)
    {
        m_count = 0;
        GenBullet();
    }
    for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end(); iter++)
    {
        iter->Update();
        UnitPos pos = iter->GetPos();
        if (pos.x < 0)
        {
            iter->SetLife(0);
        }
        if (pos.x > W_WIDTH)
        {
            iter->SetLife(0);
        }
        if (pos.y < 0)
        {
            iter->SetLife(0);
        }
        if (pos.y > W_HEIGHT)
        {
            iter->SetLife(0);
        }
    }

    for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end();)
    {
        if (iter->GetLife() == 0)
        {
            iter = m_vecBullet.erase(iter);
        }
        else
        {
            iter++;
        }
    }
    GameNode::Update();
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
    m_pPlayer->Render();
    m_pEnemy->Render();
    for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end(); iter++)
    {
        iter->Render();
    }
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "player pos x : %f  /  y : %f", m_pPlayer->GetPos().x, m_pPlayer->GetPos().y);
    TextOut(g_hDC, 0, 0, infoMsg, strlen(infoMsg));
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

void MainGame::GenBullet()
{
    Bullet genBullet("bullet");
    genBullet.SetBodyPos(m_pEnemy->GetPos());
    genBullet.SetBodySize(UnitSize{ 32, 32 });
    genBullet.SetBodyRect(g_pDrawHelper->MakeRect(genBullet.GetPos(), genBullet.GetSize()));
    genBullet.SpritesSetup(2, 2);
    double angle = g_pGeoHelper->GetAngleFromCoord(genBullet.GetPos(), m_pPlayer->GetPos());
    UnitPos pos = g_pGeoHelper->GetCoordFromAngle(angle, 10.0f);
    genBullet.SetBodySpeed((UnitSpeed)pos);

    m_vecBullet.push_back(genBullet);
}

void MainGame::PlayerController()
{
    UnitSpeed dPlayerSpd = { 0.0f, 0.0f };
    m_pPlayer->m_spritesImg->SetFrameY(0);
    if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        dPlayerSpd.x = -PLAYER_SPEED;
        m_pPlayer->m_spritesImg->SetFrameY(1);
    }
    if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        dPlayerSpd.x = PLAYER_SPEED;
        m_pPlayer->m_spritesImg->SetFrameY(2);
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
}

void MainGame::SystemController()
{
    if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
    {
        m_bIsPlaying = !m_bIsPlaying;
    }
}
