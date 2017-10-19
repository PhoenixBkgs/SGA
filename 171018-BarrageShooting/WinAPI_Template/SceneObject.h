#pragma once
#include "GameObject.h"
#include "ImageObject.h"

class SceneObject : public GameObject
{
private:
public:
    virtual void Render() override;
    
    void Setup(ImageObject* Image, UnitPos Pos);
};
