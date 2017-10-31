﻿#pragma once
#include "SceneObject.h"
#include "SpritesObject.h"

class GameScene : public SceneObject
{
private:
public:
    GameScene(E_GAME_STATE* State);
    ~GameScene();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    // SceneObject을(를) 통해 상속됨
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void DeleteScene() override;
};

