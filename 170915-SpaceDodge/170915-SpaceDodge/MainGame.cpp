#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_isPlaying = false;
    m_gameLvl = 1;
    SetGameLevel(1);
    m_eGameState = GS_LOADING;
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
        m_player.Setup();
        break;
    case GS_PLAYING:
        PlayGame();
        break;
    case GS_PAUSE:
        break;
    case GS_STAGECLEAR:
        break;
    case GS_GAMEOVER:
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
}


void MainGame::SetGameLevel(int GameLevel)
{
    int BulletCount = (GameLevel * 5) ^ 2;
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
    Bullet bulletPrefab(m_player);
    for (int i = 0; i < BulletCount; i++)
    {
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

    //  vector<Bullet> 업데이트
    for (auto iter = m_bullet.begin(); iter != m_bullet.end(); iter++)
    {
        iter->Update();
    }
    m_ui.SetInfoBar(m_gameLvl, 0);
}
