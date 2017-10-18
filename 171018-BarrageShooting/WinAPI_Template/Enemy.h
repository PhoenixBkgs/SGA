#pragma once
#include "SpritesObject.h"

#define BOSS_WIDTH      480
#define BOSS_HEIGHT     351
#define BOSS_INIT_POS_X (W_WIDTH * 0.5f)
#define BOSS_INIT_POS_Y (BOSS_HEIGHT + 50.0f) 

class Enemy : public SpritesObject
{
private:
public:
    Enemy();
    Enemy(string szTagName);
    ~Enemy();

    virtual void Update() override;

    void PatternA();
    void PatternB();
    void PatternC();
};