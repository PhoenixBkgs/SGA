#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameMap.h"

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
    

public:
    GameMap m_map;
    Player m_player;
    vector<Bullet> m_vecBullet;
    vector<Enemy> m_vecEnemy;
    HBRUSH m_brushBullet;

//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void Setup();
    void PlayerSetup();
    void EnemySetup(int EnemyCount);

    void PlayGame();

    void DrawRect(HDC hdc, RECT* Rect);
};

