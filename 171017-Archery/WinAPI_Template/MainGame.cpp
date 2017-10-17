#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    LoadAllResources();
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
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, BLACKNESS);
}

void MainGame::Reset()
{
}

void MainGame::LoadAllResources()
{
    LoadImageResources();
    LoadSoundResources();
}

void MainGame::LoadImageResources()
{
}

void MainGame::LoadSoundResources()
{
}
