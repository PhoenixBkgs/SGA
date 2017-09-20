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

    Player          m_player;
    Ball            m_ball;
    vector<Block>   m_vecBlock;
    GameMap         m_gameMap;

    POINT m_ptPlayerPos = { (int)(W_WIDTH * 0.5), W_HEIGHT - 100 };

    int     m_gameLevel;

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

    void Refresh();
};

