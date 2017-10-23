#include "stdafx.h"
#include "SplashScene.h"


SplashScene::SplashScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


SplashScene::~SplashScene()
{
}

void SplashScene::Update()
{
}

void SplashScene::Render()
{
}

void SplashScene::Setup()
{
}

void SplashScene::LoadImageResources()
{
}

void SplashScene::DeleteScene()
{
}