#pragma once
#include "GameObject.h"

class SplashScene : public GameObject
{
private:
    vector<GameObject>*     m_vecScnObj;

public:
    SplashScene();
    ~SplashScene();

#pragma region SET
    
#pragma endregion
#pragma region GET
    vector<GameObject>*     GetGameObjVec() { return m_vecScnObj; }
#pragma endregion


    virtual void Update() override;
    virtual void Render() override;
};

