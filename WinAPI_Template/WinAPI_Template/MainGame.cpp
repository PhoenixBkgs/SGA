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
    Draw2DKomastar drawer;
    drawer.DrawCircle(UnitPos{ 100.0f, 100.0f }, UnitSize{ 100, 0 }, RGBA{ 100, 0, 0, 0 });
}

void MainGame::Render()
{
}