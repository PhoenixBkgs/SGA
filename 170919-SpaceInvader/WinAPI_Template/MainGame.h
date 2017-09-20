#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameMap.h"

#define TSAR_UP 100.0f

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
    

public:
    GameMap         m_map;
    Player          m_player;
    vector<Bullet>  m_vecBullet;
    vector<Enemy>   m_vecEnemy;
    HBRUSH          m_brushBullet;
    HBRUSH          m_brushPlayer;

    bool            m_isPlaying;
    bool            m_isEnemyArriveWall;
    bool            m_tsarIsUp;
    int             m_level;
    double          m_tsarCooldown;
    int             m_playerColor;

//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void Setup(int Level);
    void Clear();
    void Reset();
    void ScreenMessgae(HDC hdc, string Message);
    void PlayerSetup();
    void EnemySetup(int EnemyCount);

    void PlayerControl();

    void DrawRect(HDC hdc, RECT* Rect);
};

