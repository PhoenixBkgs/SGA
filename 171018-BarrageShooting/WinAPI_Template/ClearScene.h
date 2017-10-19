#pragma once
#include "SceneObject.h"
#include "ImageObject.h"

class ClearScene : public SceneObject
{
private:
    vector<SceneObject>    m_vecScnObj;

public:
    ClearScene();
    ~ClearScene();

    void Render();

    void PushImage(ImageObject* Image, UnitPos Pos);
};

