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
    m_player.SetLifeCount(10);
    m_player.m_vecObstacles = &m_vecObstacle;

    m_obsGenDelayCount = OBS_GEN_DELAY;
}

void MainGame::Update()
{
    GameNode::Update();

    if (m_player.GetLifeCount() < 0)
    {
        return;
    }

    m_bgPosX -= m_runSpeed;
    if (m_bgPosX < -BG_WIDTH)
    {
        m_bgPosX = 0.0f;
    }

    m_player.Update();

    m_obsGenDelayCount--;
    if (m_obsGenDelayCount < 0)
    {
        GenerateObstacle();
        m_obsGenDelayCount = OBS_GEN_DELAY;
    }

    for (auto obstacleRenderIter = m_vecObstacle.begin(); obstacleRenderIter != m_vecObstacle.end(); obstacleRenderIter++)
    {
        obstacleRenderIter->Update();
    }

    if (g_pKeyManager->isStayKeyDown(VK_SPACE))
    {
        UnitPos pPos = m_player.GetPosition();
        pPos.y -= 5.0f;
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
    if (m_player.GetLifeCount() < 0)
    {
        return;
    }
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
    //  Draw BG
    m_bgImg->Render(g_hDC, (int)m_bgPosX, W_HEIGHT - BG_HEIGHT);
    //  Next BG
    m_bgImg->Render(g_hDC, (int)m_bgPosX + BG_WIDTH, W_HEIGHT - BG_HEIGHT);
    m_player.Render();

    for (auto obstacleRenderIter = m_vecObstacle.begin(); obstacleRenderIter != m_vecObstacle.end(); obstacleRenderIter++)
    {
        obstacleRenderIter->Render();
    }

#ifdef _DEBUG
    char infoMsg[100];
    sprintf_s(infoMsg, "SPEED : %f  / BG_POS : %f / Life : %d", m_runSpeed, m_bgPosX, m_player.GetLifeCount());
    TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}

void MainGame::GenerateObstacle()
{
    Obstacle tObstacle;
    int objWidth = 50;
    int objHeight = (rand() % 200) + 50;

    tObstacle.SetSize(UnitSize{ objWidth, objHeight });
    tObstacle.SetPosition(UnitPos{ W_WIDTH * 0.75f, W_HEIGHT - (double)objHeight });
    tObstacle.SetBodyRect(tObstacle.GetPosition(), tObstacle.GetSize());
    tObstacle.SetMoveSpeed(UnitSpeed{ -m_runSpeed , 0.0f });
    tObstacle.SetLifeCount(1);

    m_vecObstacle.push_back(tObstacle);
}
