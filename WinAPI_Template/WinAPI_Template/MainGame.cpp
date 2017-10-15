#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    Start();
    dAngle = 0.0f;
    count = 100;
    pos = m_geoHelper.GetCenterPointWindow();
    //  Set BG
    m_img = new ImageKomastar;
    m_img->Setup("images/img-ana-barrel.bmp", 1000, 600);
    m_img2 = new ImageKomastar;
    m_img2->Setup("images/CardBack.bmp", 200, 295);

    pt1 = UnitPos{ (pos.x - m_img2->GetWidth() * 0.5f), (pos.y - m_img2->GetHeight() * 0.5f) };
    pt2 = UnitPos{ (pos.x + m_img2->GetWidth() * 0.5f), (pos.y - m_img2->GetHeight() * 0.5f) };
    pt3 = UnitPos{ (pos.x - m_img2->GetWidth() * 0.5f), (pos.y + m_img2->GetHeight() * 0.5f) };
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
    count--;
    if (count < 0)
    {
        count = 100;
    }

    dAngle += 0.001f;
    if (dAngle > 360.0f)
    {
        dAngle -= 360.0f;
    }
    pt1 = m_geoHelper.GetRotateCoord(pos, pt1, dAngle);
    pt2 = m_geoHelper.GetRotateCoord(pos, pt2, dAngle);
    pt3 = m_geoHelper.GetRotateCoord(pos, pt3, dAngle);
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
    
    POINT pt[3] = {
          POINT{(LONG)pt1.x, (LONG)pt1.y}
        , POINT{(LONG)pt2.x, (LONG)pt2.y}
        , POINT{(LONG)pt3.x, (LONG)pt3.y} 
        };

    PlgBlt(g_hDC, pt, m_img2->GetMemDC(), 0, 0, m_img2->GetWidth(), m_img2->GetHeight(), NULL, 0, 0);

    char infoMsg[128];
    sprintf_s(infoMsg, "p1 : %f  /  %f", pt1.x, pt1.y);
    TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));
    sprintf_s(infoMsg, "p2 : %f  /  %f", pt2.x, pt2.y);
    TextOut(g_hDC, 10, 30, infoMsg, (int)strlen(infoMsg));
    sprintf_s(infoMsg, "p3 : %f  /  %f", pt3.x, pt3.y);
    TextOut(g_hDC, 10, 50, infoMsg, (int)strlen(infoMsg));

}