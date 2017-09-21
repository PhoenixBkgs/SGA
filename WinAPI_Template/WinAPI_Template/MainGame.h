#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Draw2DKomastar.h"

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    Player m_player;
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
};

