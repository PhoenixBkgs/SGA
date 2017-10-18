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
    m_player.SetBodyPos(UnitPos{ W_WIDTH * 0.5f, W_HEIGHT * 0.5f - 100.0f });
    m_player.SetBodySize(UnitSize{ 100, 100 });
    m_player.SetBodySpeed(UnitSpeed{ 0.0f, 0.0f });
    
    m_enemy.SetBodyPos(UnitPos{ W_WIDTH * 0.5f, 300.0f });
    m_enemy.SetBodySize(UnitSize{ 300, 300 });
    m_enemy.SetBodySpeed(UnitSpeed{ 0.0f, 0.0f });
}

void MainGame::Update()
{
    PlayerController();
    m_player.Update();
    m_enemy.Update();
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
    m_player.Render();
    m_enemy.Render();
    for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end(); iter++)
    {
        iter->Render();
    }
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "player pos x : %f  /  y : %f", m_player.GetPos().x, m_player.GetPos().y);
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
}

void MainGame::LoadSoundResources()
{
}

void MainGame::GenBullet()
{
    Bullet genBullet;
    genBullet.SetBodyPos(m_enemy.GetPos());
    genBullet.SetBodySize(UnitSize{ 10, 10 });
    double angle = g_pGeoHelper->GetAngleFromCoord(genBullet.GetPos(), m_player.GetPos());
    UnitPos pos = g_pGeoHelper->GetCoordFromAngle(angle, 10.0f);
    genBullet.SetBodySpeed((UnitSpeed)pos);

    m_vecBullet.push_back(genBullet);
}

void MainGame::PlayerController()
{
    UnitSpeed dPlayerSpd = { 0.0f, 0.0f };
    if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        dPlayerSpd.x = -5.0f;
    }
    if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        dPlayerSpd.x = 5.0f;
    }
    if (g_pKeyManager->isStayKeyDown(VK_UP))
    {
        dPlayerSpd.y = -5.0f;
    }
    if (g_pKeyManager->isStayKeyDown(VK_DOWN))
    {
        dPlayerSpd.y = 5.0f;
    }
    m_player.SetBodySpeed(dPlayerSpd);
}
