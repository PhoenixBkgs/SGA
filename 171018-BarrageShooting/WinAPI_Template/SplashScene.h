#pragma once
#include "SceneObject.h"
#include "SpritesObject.h"
#include "Button.h"

class SplashScene : public SceneObject
{
private:
    SpritesObject   m_bgImg;
    SpritesObject   m_bgDecoImg;
    SpritesObject   m_titleImg;
    StartButton     m_startBtn;
public:
    SplashScene(E_GAME_STATE* State);
    ~SplashScene();

    virtual void Update() override;
    virtual void Render() override;

    // SceneObject��(��) ���� ��ӵ�
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void DeleteScene() override;
};