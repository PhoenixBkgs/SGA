#pragma once
#include "GameUnit.h"

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100

#define PLAYER_SPAWN_X W_WIDTH * 0.5
#define PLAYER_SPAWN_Y W_HEIGHT - 100

class Player : public GameUnit
{
    //  VARS
private:
    UnitPos     m_barrelPos[2];     //  0 - startPos , 1 - destPos
    double      m_barrelLength;
    double      m_barrelAngle;
public:

    //  FUNCS
private:

public:
    Player();
    ~Player();

    void Start();
    void Update();
    void Render();
};

