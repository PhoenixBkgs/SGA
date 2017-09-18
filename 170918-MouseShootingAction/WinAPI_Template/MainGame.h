#pragma once
#include "GameNode.h"
#include "ShootingTarget.h"
#include "ShootingGallery.h"
#include <bitset>

#define TARGET_UP_DELAY 100
#define TARGET_UP_TIME 200

struct Target
{
    RECT rtBody;
    bool isUp;
    int score;
    HBRUSH brush;
};

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    E_GAME_STATE        m_currGameState;
    vector<Target>      m_vecStTarget;
    vector<Target>      m_vecBar;
    HBRUSH              m_colorWhite;
    HBRUSH              m_colorBlack;

    bool    m_isPlaying;
    bool    m_isSetup;
    bool    m_isHit;
    bool    m_isTargetUp;
    bool    m_isClickable;

    int     m_targetUpIdx;

    int     m_gameLevel;
    int     m_gameScore;
    int     m_playerLife;

    int     m_targetUpDelay;
    int     m_targetUpTime;

    int     m_maxDelay;
    int     m_maxUpTime;

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
    void CreateTargets();

    void PlayGame();
    void SetTargetUpFlag(vector<int> TargetIdx, bool Flag);

    void TargetHitChecker();
};

