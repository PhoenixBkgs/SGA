#include "stdafx.h"
#include "SceneObject.h"


SceneObject::SceneObject()
{
}


SceneObject::~SceneObject()
{
}

void SceneObject::SetComponent(GameObject GameObj)
{
    m_pScnComponents->push_back(GameObj);
}
