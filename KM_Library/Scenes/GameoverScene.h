#pragma once
#include "SceneObject.h"

class SpritesObject;
class GameoverScene : public SceneObject
{
private:
    SpritesObject*      m_gameoverBgImg;
    double              m_gameoverBgAlpha;
    SpritesObject*      m_gameoverImg;
    double              m_gameoverAlpha;

public:
    GameoverScene(E_GAME_STATE* State);
    ~GameoverScene();

    virtual void Update() override;
    virtual void Render() override;

    // SceneObject을(를) 통해 상속됨
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void DeleteScene() override;
};