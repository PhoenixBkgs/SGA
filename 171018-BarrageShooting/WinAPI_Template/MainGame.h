#pragma once
#include "GameNode.h"
#include "SceneObject.h"
#include "MapObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "StartButton.h"


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
    int                     m_count;
    bool                    m_bIsPlaying;

//  SCENE
    SceneObject             m_splashScn;
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
    void SetupClearScene();

    void PlayerController();
    void SystemController();
};