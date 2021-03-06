#pragma once
#include "GameNode.h"
#pragma region SCENE
#include "SceneObject.h"
#include "LoadingScene.h"
#include "LobbyScene.h"
#include "SplashScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include "GameoverScene.h"
#pragma endregion

#include "MapObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Button.h"


class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    E_GAME_STATE            m_currGameState;
    MapObject*              m_pMap;
    string                  m_szPlayerSelect;
    int                     m_nScore;
    bool                    m_isNewScore;
    string                  m_jsonData;

//  SCENE
    LoadingScene*           m_loadingScn;
    SplashScene*            m_readyScn;
    LobbyScene*             m_lobbyScn;
    MenuScene*              m_menuScn;
    GameScene*              m_gameScn;
    ClearScene*             m_clearScn;
    GameoverScene*          m_gameoverScn;
    vector<string>          m_vecLeaderBoard;
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

    void LoadAllResources();
    void LoadImageResources();
    void LoadSoundResources();
    void LoadLeaderboard();
    void SaveLeaderboard();

    void SetupScene();
    void ReleaseAllScene();

    void SystemController();

    vector<string> SortVector(vector<string> VecData);
};