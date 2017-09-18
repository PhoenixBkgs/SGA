#pragma once
#include "ShapeDrawer.h"
#include "Player.h"
#include "MathVectorCalc.h"

#define BULLET_SIZE 10
#define BULLET_H_SIZE 5

#define MIN_BULLET_SPEED 1.0f
#define MAX_BULLET_SPEED 3.0f

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
    HBRUSH m_brush;

public:
    Bullet(Player player);
    ~Bullet();


//=======================================================
//  FUNCTIONS
private:
    void Setup(Player player);
    double SpeedLimiter(double speed);
    void BulletReflector();
    void BulletCollider();
    void IsBulletInside();

public:
    void Update();
    void Render(HDC hdc);

    RECT* GetBulletRect() { return &m_bulletRect; }
};

