#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    Start();
}


MainGame::~MainGame()
{
    delete m_bgImg;
    delete m_img;
}

void MainGame::Start()
{
    //  Set BG
    m_bgImg = new ImageKomastar;
    m_bgImg->Setup("images/bg.bmp", BG_WIDTH, BG_HEIGHT);
    m_bgPosX = 0.0f;
    m_runSpeed = 4.0f;

    m_img = new ImageKomastar;
    m_img->Setup("images/sprites-sample.bmp", 864, 280, true, MAGENTA_COLOR);
    m_player.m_pImg = m_img;
    m_player.Start();
}

void MainGame::Update()
{
    GameNode::Update();
    m_bgPosX -= m_runSpeed;
    if (m_bgPosX < -BG_WIDTH)
    {
        m_bgPosX = 0.0f;
    }

    m_player.Update();

    if (g_pKeyManager->isStayKeyDown(VK_SPACE))
    {
        UnitPos pPos = m_player.GetPosition();
        pPos.y -= 15.0f;
        m_player.SetPosition(pPos);
    }

    if (g_pKeyManager->isOnceKeyDown(VK_UP))
    {
        m_runSpeed += 0.5f;
    }
    else if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
    {
        m_runSpeed -= 0.25f;
    }
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
    //  Draw BG
    m_bgImg->Render(g_hDC, (int)m_bgPosX, W_HEIGHT - BG_HEIGHT);
    //  Next BG
    m_bgImg->Render(g_hDC, (int)m_bgPosX + BG_WIDTH, W_HEIGHT - BG_HEIGHT);
    m_player.Render();

    char infoMsg[100];
    sprintf_s(infoMsg, "SPEED : %f  / POS : %f", m_runSpeed, m_bgPosX);
    TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));
}