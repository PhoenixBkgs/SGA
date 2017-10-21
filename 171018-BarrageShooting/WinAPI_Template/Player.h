#pragma once
#include "SpritesObject.h"
#include "Bullet.h"
#include "ProgressBarObject.h"

#define PLAYER_MAX_SHOOT_DELAY 5

#define PLAYER_SPEED    10.0f
#define PLAYER_WIDTH    60
#define PLAYER_HEIGHT   70

#define PLAYER_INIT_POS_X   (W_WIDTH * 0.5f)
#define PLAYER_INIT_POS_Y   (W_HEIGHT - 100.0f)

#define PLAYER_INIT_HP  100.0f

class Enemy;
class Player : public SpritesObject
{
private:
    Enemy*              m_pEnemy = NULL;
    vector<Bullet>      m_vecBullets;
    ProgressBarObject   m_hpBar;
    int                 m_nShootDelay = 0;
    double              m_dHp;
public:
    Player();
    Player(string szTagName);
    ~Player();

#pragma region GET
    double GetHp() { return m_dHp; }
#pragma endregion
#pragma region SET
    void    SetEnemy(Enemy* Enemy) { m_pEnemy = Enemy; }
    void    SetHp(double Hp) { m_dHp = Hp; }
    void    SumHp(double Hp) { m_dHp += Hp; }
#pragma endregion

    void SetupForProgressBar();
    virtual void Update() override;
    virtual void Render() override;

    void Shoot();
    void PlayerController();
};

