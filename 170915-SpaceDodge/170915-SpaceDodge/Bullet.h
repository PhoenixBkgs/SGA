#pragma once
#include "ShapeDrawer.h"
#include "Player.h"
#include "MathVectorCalc.h"

#define BULLET_SIZE 10
#define BULLET_H_SIZE 5

#define MIN_BULLET_SPEED 1
#define MAX_BULLET_SPEED 10

enum E_GEN_DIRECTION
{
    TOP = 0, LEFT, RIGHT, DOWN
};

class Bullet : public ShapeDrawer
{
//=======================================================
//  VARIABLES
private:
    RECT m_bulletRect;
    vector<double> m_moveSpeed;
    bool m_isInside;
    double m_bulletPosX;
    double m_bulletPosY;

public:
    Bullet(Player player);
    ~Bullet();


//=======================================================
//  FUNCTIONS
private:
    void Setup(Player player);

public:
    void Update();
    void Render(HDC hdc);

    RECT* GetBulletRect() { return &m_bulletRect; }
};

