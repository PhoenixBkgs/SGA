#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    Player                  m_player;
    Enemy                   m_enemy;
    vector<Bullet>          m_vecBullet;
    int                     m_count;
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

    void GenEnemy();
    void GenBullet();

    void PlayerController();
};