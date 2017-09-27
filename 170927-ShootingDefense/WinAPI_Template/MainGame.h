#pragma once
#include "GameNode.h"

#include "Draw2DKomastar.h"
#include "Geometry2DKomastar.h"
#include "Physics2DKomastar.h"
#include "ImageKomastar.h"

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

#define MAX_DELAY 100
#define MAX_TIMER 10000
#define LEVELING_FACTOR 0.5

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    Draw2DKomastar      m_drawHelper;
    Geometry2DKomastar  m_geoHelper;
    Physics2DKomastar   m_physicsHelper;

    Player          m_player;
    vector<Bullet>  m_vecBullet;
    vector<Enemy>   m_vecEnemy;

    int     m_gameLevel;
    int     m_gameScore;
    int     m_enemyGenDelay;
    bool    m_isGenEnemy;
    int     m_enemyCount;
    int     m_lifeTimeCount;

    bool    m_isPause;

    HBRUSH*  m_playerBrush;
    HBRUSH*  m_bulletBrush;
    HBRUSH*  m_enemyBrush;
//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;

    void Shoot();
    void GenEnemy();
    void Collider();
    void EnemyCleaner();
};

