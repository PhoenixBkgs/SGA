#pragma once
#include "GameObject.h"

class SceneObject : public GameObject
{
//  VARS
protected:
    vector<GameObject>*     m_pScnComponents;

//  FUNCS
public:
    SceneObject();
    ~SceneObject();

#pragma region GET
    vector<GameObject>*     GetComponents() { return m_pScnComponents; }
#pragma endregion
#pragma region SET
    void        SetComponent(GameObject GameObj);
#pragma endregion
};