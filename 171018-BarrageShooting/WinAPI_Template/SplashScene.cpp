#include "stdafx.h"
#include "SplashScene.h"


SplashScene::SplashScene()
{
}


SplashScene::~SplashScene()
{
}

void SplashScene::Update()
{
}

void SplashScene::Render()
{
    for (auto iter = m_vecScnObj.begin(); iter != m_vecScnObj.end(); iter++)
    {
        iter->Render();
    }
}