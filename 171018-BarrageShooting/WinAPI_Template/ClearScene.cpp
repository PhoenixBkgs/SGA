#include "stdafx.h"
#include "ClearScene.h"


ClearScene::ClearScene()
{
}


ClearScene::~ClearScene()
{
}

void ClearScene::Render()
{
    for (auto iter = m_vecScnObj.begin(); iter != m_vecScnObj.end(); iter++)
    {
        iter->Render();
    }
}

void ClearScene::PushImage(ImageObject * Image, UnitPos Pos)
{
    SceneObject scnObj;
    scnObj.Setup(Image, Pos);

    m_vecScnObj.push_back(scnObj);
}
