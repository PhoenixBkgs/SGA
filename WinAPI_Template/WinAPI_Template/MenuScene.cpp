#include "stdafx.h"
#include "MenuScene.h"

MenuScene::MenuScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


MenuScene::~MenuScene()
{
}

void MenuScene::Update()
{

}

void MenuScene::Render()
{
}

void MenuScene::LoadImageResources()
{
}

void MenuScene::Setup()
{
}

void MenuScene::DeleteScene()
{
}
