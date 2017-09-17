#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(Player player)
{
    Setup(player);
}


Bullet::~Bullet()
{
}

void Bullet::Setup(Player player)
{
    bool m_isInside = false;

    E_GEN_DIRECTION eGenDirection = (E_GEN_DIRECTION)(rand() % 4);
    Sleep((int)eGenDirection);
    srand(time(NULL) * (int)eGenDirection * 50);
    int bulletPosX = (rand() % 500) + 100;
    int bulletPosY = (rand() % 500) + 100;

    switch (eGenDirection)
    {
    case TOP:
        bulletPosY -= WIN_HEIGHT;
        break;
    case LEFT:
        bulletPosX -= WIN_WIDTH;
        break;
    case RIGHT:
        bulletPosX += WIN_WIDTH;
        break;
    case DOWN:
        bulletPosY += WIN_HEIGHT;
        break;
    default:
        break;
    }

    m_bulletRect.left = bulletPosX;
    m_bulletRect.right = bulletPosX + BULLET_SIZE;
    m_bulletRect.top = bulletPosY;
    m_bulletRect.bottom = bulletPosY + BULLET_SIZE;

    m_bulletPosX = m_bulletRect.left;
    m_bulletPosY = m_bulletRect.top;

    POINT ptPlayer;
    POINT ptBulletPos;
    vector<double> vecDirection;
    MathVectorCalc vCalc;
    ptPlayer = player.GetPlayerPos();
    ptBulletPos.x = bulletPosX;
    ptBulletPos.y = bulletPosY;
    vecDirection = vCalc.GetDirection(ptPlayer, ptBulletPos, 0.01f);

    m_moveSpeed.push_back(vecDirection[0]);
    m_moveSpeed.push_back(vecDirection[1]);
}

void Bullet::Update()
{
    //  총알이 안에 있을때
    if (m_isInside == true)
    {
        BulletReflector();
    }
    else
    {
        IsBulletInside();
    }

    m_moveSpeed[0] = SpeedLimiter(m_moveSpeed[0]);
    m_moveSpeed[1] = SpeedLimiter(m_moveSpeed[1]);
    m_bulletPosX += m_moveSpeed[0];
    m_bulletPosY += m_moveSpeed[1];

    m_bulletRect.left = (LONG)(m_bulletPosX);
    m_bulletRect.right = (LONG)(m_bulletPosX + BULLET_SIZE);
    m_bulletRect.top = (LONG)(m_bulletPosY);
    m_bulletRect.bottom = (LONG)(m_bulletPosY + BULLET_SIZE);

    
}

void Bullet::Render(HDC hdc)
{
    DrawRectangle(hdc, m_bulletRect);
}

//  최소 속도와 최대 속도 제한
double Bullet::SpeedLimiter(double speed)
{
    double retSpeed = speed;
    if (speed > 0.0f)
    {
        if (speed < MIN_BULLET_SPEED)
        {
            retSpeed = MIN_BULLET_SPEED;
        }
        else if (speed > MAX_BULLET_SPEED)
        {
            retSpeed = MAX_BULLET_SPEED;
        }
    }
    else
    {
        if (speed > -MIN_BULLET_SPEED)
        {
            retSpeed = -MIN_BULLET_SPEED;
        }
        else if (speed < -MAX_BULLET_SPEED)
        {
            retSpeed = -MAX_BULLET_SPEED;
        }
    }

    return retSpeed;
}

void Bullet::BulletReflector()
{
    srand(time(NULL));
    int accelX = rand() % 100;
    srand(time(NULL) * accelX);
    int accelY = rand() % 100;
    
    //double dAccelX = accelX * 0.0001f;
    //double dAccelY = accelY * 0.0001f;

    double dAccelX = 1.01f;
    double dAccelY = 1.01f;

    if ((m_bulletRect.left <= 0))
    {
        m_moveSpeed[0] = -m_moveSpeed[0];
        m_moveSpeed[0] *= dAccelX;
    }
    if (m_bulletRect.right >= WIN_WIDTH - 5)
    {
        m_moveSpeed[0] = -m_moveSpeed[0];
        m_moveSpeed[0] *= dAccelX;
    }
    if (m_bulletRect.top <= 0)
    {
        m_moveSpeed[1] = -m_moveSpeed[1];
        m_moveSpeed[1] *= dAccelY;
    }
    if (m_bulletRect.bottom >= (WIN_HEIGHT - 44))
    {
        m_moveSpeed[1] = -m_moveSpeed[1];
        m_moveSpeed[1] *= dAccelY;
    }
    
}

void Bullet::IsBulletInside()
{
    if ((m_bulletRect.left > 0) && (m_bulletRect.right < WIN_WIDTH))
    {
        if ((m_bulletRect.top > 0) && (m_bulletRect.bottom < (WIN_HEIGHT - 44)))
        {
            m_isInside = true;
        }
    }
}
