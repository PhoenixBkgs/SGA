#pragma once
#include "SceneObject.h"
#include "SpritesObject.h"

class MenuScene : public SceneObject
{
private:
    SpritesObject       m_pauseBgImg;
    SpritesObject       m_menuImg;

public:
    MenuScene(E_GAME_STATE* State);
    ~MenuScene();

    virtual void Update() override;
    virtual void Render() override;

    virtual void LoadImageResources() override;
    virtual void Setup() override;
    virtual void DeleteScene() override;
};