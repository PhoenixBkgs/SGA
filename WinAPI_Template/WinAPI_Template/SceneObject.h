#pragma once
#include "GameObject.h"

class SceneObject : public GameObject
{
//------------------------------------------------------------
//  VARS
//------------------------------------------------------------
protected:
    E_GAME_STATE*   m_currGameState;
//------------------------------------------------------------
//  FUNCS
public:
    SceneObject();
    ~SceneObject();

#pragma region VIRTUAL
    virtual void Setup() PURE;
    virtual void LoadImageResources() PURE;
    virtual void DeleteScene() PURE;
#pragma endregion

#pragma region SET
    void SyncGameState(E_GAME_STATE* State) { m_currGameState = State; }
#pragma endregion
//------------------------------------------------------------
};