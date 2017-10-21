#pragma once
#include "SceneObject.h"
#include "SpritesObject.h"

class LoadingScene : public SceneObject
{
private:
    SpritesObject       m_logo;
public:
    LoadingScene(E_GAME_STATE* State);
    ~LoadingScene();

    virtual void Update() override;
    virtual void Render() override;

    // SceneObject��(��) ���� ��ӵ�
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void AddComponentsToScene() override;
    virtual void DeleteScene() override;
};
