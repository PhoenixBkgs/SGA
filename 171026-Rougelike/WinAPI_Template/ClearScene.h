#pragma once
#include "SceneObject.h"

class SpritesObject;
class ClearScene : public SceneObject
{
private:
    int     m_nGameTimer;

public:
    ClearScene(E_GAME_STATE* State);
    ~ClearScene();

    void    SetGameTimer(int GameTimer) { m_nGameTimer = GameTimer; }

    virtual void Update() override;
    virtual void Render() override;

    // SceneObject을(를) 통해 상속됨
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void DeleteScene() override;
};