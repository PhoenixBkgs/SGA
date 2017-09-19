#pragma once
#include "GameUnit.h"
#include "GameMap.h"
#include "Bullet.h"

#define PLAYER_SIZE     40
#define PLAYER_SPEED    5

class Player : public GameUnit
{
//  VARS
public:
    GameMap m_map;
    POINT   m_ptPlayerPos;

    int     m_playerSpeed;

//  FUNCS
public:
    Player();
    ~Player();

    void IsInsideWindow(bool IsStop);
    vector<Bullet> Shot(int BulletSpeed, E_WEAPON_TYPE WeaponType, HBRUSH Brush);
    POINT GetTurretPos();
    int GetPlayerSize() { return PLAYER_SIZE; }
};

