#pragma once
#include "GameNode.h"
#include "ShootingTarget.h"
#include "ShootingGallery.h"
#include <bitset>

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    E_GAME_STATE        m_currGameState;
    ShootingGallery     m_map;

    int     m_entireTargetCount;
    int     m_gameLevel;
    int     m_gameScore;
    int     m_playerLife;

    int     m_targetUptime;
    int     m_targetUpInterval;
    bool    m_isHit;

    bitset<4>  m_cheatMode;

public:

//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void SetCheatMode(E_CHEAT_MODE CheatCode);
    bitset<4> GetCheatMode() { return m_cheatMode; }
    void InputModule();

    void Setup();

    void PlayGame();

    void TargetHitChecker();
};

