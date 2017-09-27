#pragma once
#include "GameUnit.h"

#define MOVE_SPEED 5.0f

class Enemy : public GameUnit
{
public:
    Enemy();
    ~Enemy();

    void Update();
    void Render();
    void MoveRestricter();
};

