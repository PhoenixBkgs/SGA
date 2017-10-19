#include "stdafx.h"
#include "SplashScene.h"


SplashScene::SplashScene()
{
}


SplashScene::~SplashScene()
{
}

void SplashScene::Render()
{
    for (auto iter = m_vecScnObj.begin(); iter != m_vecScnObj.end(); iter++)
    {
        iter->Render();
    }
}

void SplashScene::PushImage(ImageObject * Image, UnitPos Pos)
{
    SceneObject scnObj;
    scnObj.Setup(Image, Pos);

    m_vecScnObj.push_back(scnObj);
}
