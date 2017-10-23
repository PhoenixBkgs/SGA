#pragma once
#include "SceneObject.h"

class SpritesObject;
class ClearScene : public SceneObject
{
private:
    int                 m_nScore;
    SpritesObject*      m_scoreObject;

    SpritesObject*      m_clearBgImg;
    double              m_clearBgAlpha;
    SpritesObject*      m_continueImg;
    double              m_continueAlpha;

public:
    ClearScene(E_GAME_STATE* State);
    ~ClearScene();

    void    SetScore(int Score) { m_nScore = Score; }
    int     GetScore() { return m_nScore; }

    virtual void Update() override;
    virtual void Render() override;

    // SceneObject을(를) 통해 상속됨
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void DeleteScene() override;
};