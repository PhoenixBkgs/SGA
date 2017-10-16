#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    Start();
    dAngle = 0.0f;
    count = 1;
    pos = m_geoHelper.GetCenterPointWindow();
    //  Set BG
    m_img = new ImageObject;
    m_img->Setup("images/img-ana-barrel.bmp", 1000, 600);
    m_img2 = new ImageObject;
    m_img2->Setup("images/hots-logo-blade.bmp", 900, 900);
    m_img2->SetupForAlphaBlend();
}


MainGame::~MainGame()
{
    delete m_img;
    delete m_img2;
}

void MainGame::Start()
{
    
}

void MainGame::Update()
{
    GameNode::Update();
    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
    }
    count--;
    if (count < 0)
    {
        count = 1;
        dAngle += 1.0f;
        if (dAngle > 360.0f)
        {
            dAngle -= 360.0f;
        }
    }
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, BLACKNESS);

    m_img->Render(g_hDC);

    RECT rt = { 100, 100, 200, 200 };
    m_img2->Render(g_hDC, UnitPos{ W_WIDTH / 2, W_HEIGHT / 2 }, dAngle);

    char infoMsg[128];
    sprintf_s(infoMsg, "angle : %f", dAngle);
    TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));
}