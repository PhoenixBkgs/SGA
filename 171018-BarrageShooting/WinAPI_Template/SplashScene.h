#pragma once
#include "SceneObject.h"
#include "ImageObject.h"

class SplashScene : public SceneObject
{
private:
    vector<SceneObject>    m_vecScnObj;

public:
    SplashScene();
    ~SplashScene();

    void Render();

    void PushImage(ImageObject* Image, UnitPos Pos);
};

