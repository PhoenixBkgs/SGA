#pragma once
#include "GameUnit.h"
#include "GameMap.h"
#include "Bullet.h"

#define PLAYER_SIZE     40

class Player : public GameUnit
{
//  VARS
public:
    GameMap m_map;
    int     m_playerSpeed;
    POINT   m_ptPlayerPos;

//  FUNCS
public:
    Player();
    ~Player();

    void IsInsideWindow(bool IsStop);
    Bullet Shot(int BulletSpeed, HBRUSH Brush);
    POINT GetTurretPos();
    int GetPlayerSize() { return PLAYER_SIZE; }
};

