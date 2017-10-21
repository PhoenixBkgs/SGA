#pragma once
#include "GameNode.h"
#pragma region SCENE
#include "SceneObject.h"
#include "LoadingScene.h"
#include "SplashScene.h"
#include "MenuScene.h"
#include "GameScene.h"
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
    Player*                 m_pPlayer;
    Enemy*                  m_pEnemy;
    vector<Bullet>          m_vecBullet;

//  SCENE
    LoadingScene*           m_loadingScn;
    SplashScene*            m_splashScn;
    MenuScene*              m_menuScn;
    GameScene*              m_gameScn;
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

    void SetupScene();
    void ReleaseAllScene();

    void SystemController();
};