#pragma once
#include "GameUnit.h"
#include "Geometry2DKomastar.h"

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100

#define PLAYER_SPAWN_X W_WIDTH * 0.5
#define PLAYER_SPAWN_Y W_HEIGHT - 100

#define PLAYER_SPEED    5.0f

class Player : public GameUnit
{
    //  VARS
private:
    Geometry2DKomastar m_geoHelper;

    UnitPos     m_barrelPos[2];     //  0 - startPos , 1 - destPos
    double      m_barrelLength;

public:
    double      m_barrelAngle;

    //  FUNCS
private:

public:
    Player();
    ~Player();

    void Start();
    void Update();
    void Render();

    UnitPos GetBarrelPos() { return m_barrelPos[1]; }
};

