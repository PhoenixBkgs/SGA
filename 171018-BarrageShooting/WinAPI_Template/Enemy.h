#pragma once
#include "SpritesObject.h"
#include "Bullet.h"
#include "ProgressBarObject.h"

#define ENEMY_MAX_SHOOT_DELAY 20

#define BOSS_WIDTH      480
#define BOSS_HEIGHT     351

#define BOSS_INIT_POS_X (W_WIDTH * 0.5f)
#define BOSS_INIT_POS_Y (BOSS_HEIGHT * 0.5f + 10.0f) 

#define BOSS_INIT_HP    1000.0f

class Player;
class Enemy : public SpritesObject
{
private:
    vector<Bullet>*     m_vecBullets;
    vector<Bullet>::iterator m_iterBullet;
    Player*             m_pPlayer;
    ProgressBarObject   m_hpBar;
    bool                m_bIsReload;
    int                 m_nCShootCount;
    int                 m_nCShootMax;
    int                 m_nShootDelayMax;
    int                 m_nShootDelay = 0;
    double              m_dHp;

public:
    Enemy();
    Enemy(string szTagName);
    ~Enemy();

#pragma region GET
    double      GetHp() { return m_dHp; }
#pragma endregion

#pragma region SET
    void    SetPlayer(Player* Player) { m_pPlayer = Player; }
    void    SetHp(double Hp) { m_dHp = Hp; }
    void    SumHp(double Hp) { m_dHp += Hp; }
    void    SetBullet(vector<Bullet>* Bullets) { m_vecBullets = Bullets; }
#pragma endregion

    virtual void Update() override;
    virtual void Render() override;

    void Shoot();

    void SetupForProgressBar();
    void PatternA();
    void PatternB(double angle);
    void PatternC();
};