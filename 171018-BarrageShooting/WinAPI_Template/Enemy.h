#pragma once
#include "SpritesObject.h"
#include "Bullet.h"

#define ENEMY_MAX_SHOOT_DELAY 20

#define BOSS_WIDTH      480
#define BOSS_HEIGHT     351

#define BOSS_INIT_POS_X (W_WIDTH * 0.5f)
#define BOSS_INIT_POS_Y (BOSS_HEIGHT * 0.5f + 10.0f) 

class Player;
class Bullet;
class Enemy : public SpritesObject
{
private:
    vector<Bullet>      m_vecBullets;
    Player*             m_pPlayer;
    int                 m_nShootDelay = 0;
public:
    Enemy();
    Enemy(string szTagName);
    ~Enemy();

#pragma region GET

#pragma endregion

#pragma region SET
    void    SetPlayer(Player* Player) { m_pPlayer = Player; }
#pragma endregion

    virtual void Update() override;
    virtual void Render() override;

    void Shoot();

    void PatternA();
    void PatternB();
    void PatternC();
};