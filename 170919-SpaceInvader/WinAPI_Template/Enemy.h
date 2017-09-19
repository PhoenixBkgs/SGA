#pragma once
#include "GameUnit.h"

#define MAX_ENEMY       50
#define ENEMY_ROW       5
#define ENEMY_COL       10
#define ENEMY_SIZE      20
#define ENEMY_SPEED     5

class Enemy : public GameUnit
{
public:
    Enemy();
    ~Enemy();
};

