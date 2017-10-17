#pragma once
#pragma region INCLUDE_HEADERS
#include "GameNode.h"
#include "ArcheryStadium.h"
#include "Player.h"
#include "Arrow.h"
#include "Target.h"
#include "Wind.h"
#include "ScoreBoard.h"
#pragma endregion

#pragma region MUTUAL_REF
#pragma endregion


class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    map<string, string> m_mapDebugMsg;
    ArcheryStadium      m_stadium;
    Player              m_player;
    Arrow               m_arrow;
    Target              m_target;
    Wind                m_wind;
    ScoreBoard          m_scoreBoard;
//=======================================================

//  FUNCTIONS
private:
    E_GAME_STATE    m_currGameState;
    E_GAME_STATE    m_prevGameState;

public:
    MainGame();
    ~MainGame();

#pragma region GET
    E_GAME_STATE GetCurrGameState() { return m_currGameState; }
#pragma endregion

#pragma region SET
    void    SetCurrGameState(E_GAME_STATE State) { m_currGameState = State; }
#pragma endregion


    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    void Reset();

    void LoadAllResources();
    void LoadImageResources();
    void LoadSoundResources();

#pragma region USER_CONTROL
    void PlayerController();
    void SystemController();
#pragma endregion
};