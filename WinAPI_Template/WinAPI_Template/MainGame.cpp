#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    Start();
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
    //  SAMPLE CODES
    /*
    UnitPos centerPoint = m_geoHelper.GetCenterPointWindow();
    UnitPos mousePos = { (double)g_ptMouse.x, (double)g_ptMouse.y };
    double angle = m_geoHelper.GetAngleFromCoord(centerPoint, mousePos);

    UnitPos destPos = m_geoHelper.GetCoordFromAngle(angle, 100.0f);
    destPos.x += centerPoint.x;
    destPos.y += centerPoint.y;
    m_drawHelper.DrawLine2D(centerPoint, destPos, 5, RGBA{255, 0, 0, 0});
    char infoMsg[100];
    sprintf_s(infoMsg, "DEGREE : %f", angle);
    TextOut(g_hDC, centerPoint.x, centerPoint.y, infoMsg, strlen(infoMsg));
    sprintf_s(infoMsg, "X : %f // Y : %f", destPos.x, destPos.y);
    TextOut(g_hDC, destPos.x, destPos.y, infoMsg, strlen(infoMsg));


    RECT rt = { 100, 100, 300, 300 };
    int r = 0;
    int b = 0;
    if (m_physicsHelper.PtInsideRect(mousePos, rt))
    {
        r = 150;
    }
    else
    {
        b = 150;
    }
    Rectangle(g_hDC, rt.left, rt.top, rt.right, rt.bottom);
    FillRect(g_hDC, &rt, CreateSolidBrush(RGB(r, 0, b)));
    */
}