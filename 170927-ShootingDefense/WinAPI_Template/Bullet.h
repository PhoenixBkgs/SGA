#pragma once
#include "GameUnit.h"

#define BULLET_SPEED 10.0f
#define BULLET_SIZE 10

class Bullet : public GameUnit
{
public:
    Bullet();
    Bullet(UnitPos GenPos);
    ~Bullet();

    void Update();
    void Render();
};

