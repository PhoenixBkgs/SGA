#pragma once
#include "SceneObject.h"

class SpritesObject;
class ClearScene : public SceneObject
{
private:
    SpritesObject*      m_clearBgImg;
    double              m_clearBgAlpha;
    SpritesObject*      m_continueImg;
    double              m_continueAlpha;

    int*                m_pScore;
public:
    ClearScene(E_GAME_STATE* State);
    ~ClearScene();

    void SetScore(int* Score) { m_pScore = Score; }

    virtual void Update() override;
    virtual void Render() override;

    // SceneObject을(를) 통해 상속됨
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void DeleteScene() override;
};