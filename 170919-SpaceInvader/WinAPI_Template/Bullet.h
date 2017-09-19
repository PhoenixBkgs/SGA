#pragma once
#include "GameUnit.h"


#define BULLET_SPEED 5

class Bullet : public GameUnit 
{
public:
    bool m_isHit;

public:
    Bullet();
    ~Bullet();
};

