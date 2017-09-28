#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    Start();
    m_rt = { 0, 0, 200, 100 };
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
    m_rt.left += 1;
    m_rt.right += 1;
    m_rt.top += 1;
    m_rt.bottom += 1;
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);

    HBRUSH hBrush;
    HFONT hFont;
    HFONT hTmp;

    hBrush = CreateSolidBrush(RGB(255, 0, 0));
    FillRect(g_hDC, &m_rt, hBrush);
    DeleteObject(hBrush);
    SetTextColor(g_hDC, RGB(255, 255, 255));
    hFont = CreateFont(30, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 2, 0, TEXT("Consolas"));
    hTmp = (HFONT)SelectObject(g_hDC, hFont);
    SetBkMode(g_hDC, TRANSPARENT);
    string strTest = "±Ã¼­Ã¼";
    DrawText(g_hDC, strTest.data(), -1, &m_rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    DeleteObject(SelectObject(g_hDC, hTmp));

    m_drawHelper.DrawCenterText("Áß¾Ó", 100, _RGBA{ 250, 250, 250, 0 }, "±Ã¼­");
}