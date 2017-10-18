#pragma once
#include "SpritesObject.h"
#include "Bullet.h"

#define MAX_SHOOT_DELAY 10

#define PLAYER_SPEED    10.0f
#define PLAYER_WIDTH    60
#define PLAYER_HEIGHT   70

#define PLAYER_INIT_POS_X   (W_WIDTH * 0.5f)
#define PLAYER_INIT_POS_Y   (W_HEIGHT - 100.0f)

class Enemy;
class Player : public SpritesObject
{
private:
    Enemy*              m_pEnemy = NULL;
    vector<Bullet>      m_vecBullets;
    int                 m_nShootDelay = 0;
public:
    Player();
    Player(string szTagName);
    ~Player();

#pragma region GET

#pragma endregion
#pragma region SET
    void    SetEnemy(Enemy* Enemy) { m_pEnemy = Enemy; }
#pragma endregion


    virtual void Update() override;
    virtual void Render() override;

    void Shoot();
};

