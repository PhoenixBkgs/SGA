#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_eGameState = GS_READY;
    SetGame();
}


MainGame::~MainGame()
{
}

void MainGame::Update()
{
    GameNode::Update();
    

    switch (m_eGameState)
    {
    case GS_LOADING:
        m_eGameState = GS_READY;
        break;
    case GS_READY:
        break;
    case GS_PLAYING:
        PlayGame();
        break;
    case GS_PAUSE:
        break;
    case GS_STAGECLEAR:
        break;
    case GS_GAMEOVER:
        SetGame();
        break;
    default:
        break;
    }

    GetKeyState();
}

void MainGame::Render(HDC hdc)
{
    m_player.Render(hdc);
    m_ui.DrawInfoBar(&hdc);
    for (auto iter = m_bullet.begin(); iter != m_bullet.end(); iter++)
    {
        iter->Render(hdc);
    }
    if (m_eGameState == GS_GAMEOVER)
    {
        m_ui.Render(hdc);
    }
}


void MainGame::SetGame()
{
    m_player.Setup();
    ClearRainOfBullet();
    m_gameLvl = 1;
    SetGameLevel(m_gameLvl);
    m_bulletRegenCounter = (int)(500 / m_gameLvl);
}

void MainGame::SetGameLevel(int GameLevel)
{
    int BulletCount = (GameLevel * 5);
    CreateBarrage(BulletCount);
}

void MainGame::GetKeyState()
{
    if (GetAsyncKeyState(VK_RETURN) & 0x8000)
    {
        switch (m_eGameState)
        {
        case GS_READY:
            m_eGameState = GS_PLAYING;
            break;
        case GS_STAGECLEAR:
        case GS_GAMEOVER:
            m_eGameState = GS_READY;
            break;
        default:
            break;
        }
    }
}


void MainGame::CreateBarrage(int BulletCount)
{
    for (int i = 0; i < BulletCount; i++)
    {
        Bullet bulletPrefab(m_player);
        m_bullet.push_back(bulletPrefab);
    }
}

void MainGame::ClearRainOfBullet()
{
    m_bullet.clear();
}

void MainGame::DrawBarrage(HDC hdc)
{
    for (auto iter = m_bullet.begin(); iter != m_bullet.end(); iter++)
    {
        iter->Render(hdc);
    }
}

void MainGame::PlayGame()
{
    //  Player 업데이트
    m_player.Update();

    if (m_bulletRegenCounter <= 0)
    {
        Bullet tempBullet(m_player);
        m_bullet.push_back(tempBullet);
        m_bulletRegenCounter = (int)(500 / m_gameLvl);
        m_gameLvl += 1;
    }
    m_bulletRegenCounter--;

    //  vector<Bullet> 업데이트
    for (auto iter = m_bullet.begin(); iter != m_bullet.end(); iter++)
    {
        iter->Update();
        if (Collider(&m_player.GetPlayerRect(), iter->GetBulletRect()))
        {
            //  PLAYER DEAD
            m_eGameState = GS_GAMEOVER;
        }
    }
    m_ui.SetInfoBar(m_gameLvl, 0);

    //if (GetAsyncKeyState(VK_LBUTTON & 0x0001))
}

bool MainGame::Collider(RECT* rt1, RECT* rt2)
{
    RECT tempRt;
    return IntersectRect(&tempRt, rt1, rt2);
}


