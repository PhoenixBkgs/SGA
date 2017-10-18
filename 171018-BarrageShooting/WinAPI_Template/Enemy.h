#pragma once
#include "SpritesObject.h"
#include "Bullet.h"

#define BOSS_WIDTH      480
#define BOSS_HEIGHT     351
#define BOSS_INIT_POS_X (W_WIDTH * 0.5f)
#define BOSS_INIT_POS_Y (BOSS_HEIGHT + 50.0f) 

class Bullet;
class Enemy : public SpritesObject
{
private:
    vector<Bullet>   m_vecBullets;

public:
    Enemy();
    Enemy(string szTagName);
    ~Enemy();

#pragma region GET

#pragma endregion

#pragma region SET
    void    PushBullet(Bullet Bullet);
#pragma endregion

    virtual void Update() override;
    virtual void Render() override;

    void PatternA();
    void PatternB();
    void PatternC();
};