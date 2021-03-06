#pragma once
#include "GameNode.h"
#include "json.hpp"
#include "MapGenerator.h"

#pragma region SCENE
#include "LoadingScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include "GameoverScene.h"
#pragma endregion

using json = nlohmann::json;
class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    ImageObject*    m_pImgMinimap;
	HBRUSH			m_brush;

    E_GAME_STATE    m_gameState;
    LoadingScene*   m_scnLoading;
    GameScene*      m_scnGame;
    ClearScene*     m_scnClear;
    GameoverScene*  m_scnOver;

    MapGenerator    m_mapGen;
    UnitSize        m_nMapSize;
//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    void Reset();

#pragma region RESOURCES
    void LoadAllResources();
    void LoadImageResources();
    void LoadSoundResources();
#pragma endregion
#pragma region CONTROLLER
    void    SystemController();
    void    MouseLock();
    void    MouseUnlock();
#pragma endregion
};