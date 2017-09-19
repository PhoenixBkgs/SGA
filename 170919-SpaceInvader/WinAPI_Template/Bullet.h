#pragma once
#include "GameUnit.h"


#define BULLET_SPEED 5

class Bullet : public GameUnit 
{
public:
    bool m_isHit;
    E_WEAPON_TYPE m_shotType;

public:
    Bullet();
    ~Bullet();
};

