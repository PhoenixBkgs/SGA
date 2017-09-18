#pragma once
#include "GameNode.h"
#include "ShootingGallery.h"

enum E_GAME_STATE
{
    GS_READY = 0, GS_PLAYING, GS_CLEAR, GS_GAMEOVER, GS_END
};

enum E_TARGET_SIZE
{
    TS_SMALL = 0, TS_MEDIUM, TS_LARGE, TS_END
};

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    E_GAME_STATE        m_currGameState;
    ShootingGallery     m_map;

    int     m_gameLevel;
    int     m_gameScore;
    int     m_playerLife;

public:

//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void Setup();
};

