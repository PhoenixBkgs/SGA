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
    E_WEAPON_TYPE       m_weaponType;
    Enemy*              m_pEnemy = NULL;
    vector<Bullet>*     m_vecBullets;
    ProgressBarObject   m_hpBar;
    int                 m_nShootDelay = 0;
    double              m_dHp;
    int*                m_pScore;
public:
    Player();
    Player(string szTagName);
    ~Player();

#pragma region GET
    double  GetHp() { return m_dHp; }
    int*    GetScore() { return m_pScore; }
    E_WEAPON_TYPE   GetWeaponType() { return m_weaponType; }
#pragma endregion
#pragma region SET
    //  MUTUAL REF
    void    SetEnemy(Enemy* Enemy) { m_pEnemy = Enemy; }
    void    SetBullet(vector<Bullet>* Bullets) { m_vecBullets = Bullets; }
    void    SetHp(double Hp) { m_dHp = Hp; }
    void    SumHp(double Hp) { m_dHp += Hp; }
    void    SetScore(int Score) { *m_pScore = Score; }
    void    SumScore(int Score) { *m_pScore += Score; }
    void    SetWeaponType(E_WEAPON_TYPE Type) { m_weaponType = Type; }
#pragma endregion

    void SetupForProgressBar();
    virtual void Update() override;
    virtual void Render() override;

    void Shoot();
    void PlayerController();
};

