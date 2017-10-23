#pragma once
#include "SceneObject.h"
#include "SpritesObject.h"

class LoadingScene : public SceneObject
{
private:

public:
    LoadingScene(E_GAME_STATE* State);
    ~LoadingScene();

    virtual void Update() override;
    virtual void Render() override;

    // SceneObject을(를) 통해 상속됨
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void DeleteScene() override;
};

