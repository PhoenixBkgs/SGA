#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::Update()
{
    GameNode::Update();

    switch (m_currGameState)
    {
    case GS_READY:
        break;
    case GS_PLAYING:
        break;
    case GS_CLEAR:
        break;
    case GS_GAMEOVER:
        break;
    case GS_END:
        break;
    default:
        break;
    }
}

void MainGame::Render(HDC hdc)
{
    
}

void MainGame::Setup()
{
    m_gameLevel = 1;
    m_gameScore = 0;
    m_playerLife = 10;
}
