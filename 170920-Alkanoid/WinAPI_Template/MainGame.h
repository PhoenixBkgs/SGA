#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Ball.h"
#include "Block.h"
#include "NumberGenerator.h"
#include "GameMap.h"
#include "Physics2DKomastar.h"

#define     BLOCK_COL   5
#define     BLOCK_ROW   5

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    E_GAME_STATE    m_currGameState;
    Physics2DKomastar m_physics;
    Geometry2DKomastar m_geoHelper;

    Player          m_player;
    Ball            m_ball;
    vector<Block>   m_vecBlock;
    vector<Block>   m_vecItemBlock;
    GameMap         m_gameMap;

    UnitPos         m_ptPlayerPos = { (double)(W_WIDTH * 0.5), (double)(W_HEIGHT - 100) };

    double  m_itemChance;
    double  m_antiMisfortune;

    int     m_gameLevel;
    bool    m_isSetup;

public:

//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;

    void SystemControl();
    void PlayerControl();

    void SetupGame(int Level);

    void SetupPlayer();
    void SetupBall();
    void SetBlock(int LifeCount);

    void PlayGame();
    void IsEnd();

    void Refresh();

    double RollingDice();
    void AntiMisfortune();

    bool PlayerBlockCollision(Block BlockRect);
    void BallPlayerCollision();
    E_REFLECT_DIR BallBlockCollision(Block BlockRect);
};

