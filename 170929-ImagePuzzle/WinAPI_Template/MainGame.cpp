#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_img = new ImageKomastar;
    m_img->Setup("images/hots-splash-img.bmp", 1200, 600);

    Start();
}


MainGame::~MainGame()
{
    delete m_img;
}

void MainGame::Start()
{
    m_puzzleUnit.SetPuzzleImage(m_img);
    m_puzzleUnit.SetPuzzlePos(UnitSize{ 100, 100 });
    m_puzzleUnit.SetPuzzleSize(UnitSize{ 100, 100 });

    m_puzzleUnit2.SetPuzzleImage(m_img);
    m_puzzleUnit2.SetPuzzlePos(UnitSize{ 200, 100 });
    m_puzzleUnit2.SetPuzzleSize(UnitSize{ 100, 100 });

}

void MainGame::Update()
{
    GameNode::Update();
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);

    m_puzzleUnit.Render();
    m_puzzleUnit2.Render();
}