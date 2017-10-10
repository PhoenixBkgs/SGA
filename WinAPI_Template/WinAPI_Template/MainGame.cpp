#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    Start();
    m_img = new ImageKomastar;
    m_img->Setup("images/sprites-sample.bmp", 864, 280, true, MAGENTA_COLOR);
    m_player.m_pImg = m_img;
}


MainGame::~MainGame()
{
}

void MainGame::Start()
{
}

void MainGame::Update()
{
    GameNode::Update();
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
    m_player.Render();
}