#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::Update()
{
}

void MainGame::Render(HDC hdc)
{
    TextOut(hdc, 10, 10, L"TEXT TEST", strlen("TEXT TEST"));
}