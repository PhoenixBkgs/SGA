#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
    srand((int)time(NULL));

    m_LifeCount = rand() % 5;

    m_unitSize.w = m_LifeCount * 20;
    m_unitSize.h = m_unitSize.w;

    m_moveSpeed.x = MOVE_SPEED;
    m_moveSpeed.y = 0.0f;

    int genDir = rand() % 1000;
    if (genDir > 500)
    {
        //  gen left
        m_unitPos.x = (double)-m_unitSize.w;
    }
    else
    {
        //  gen right
        m_unitPos.x = (double)(W_WIDTH + m_unitSize.w);
        m_moveSpeed.x *= -1.0f;
    }
    m_unitPos.y = (double)(rand() % 400);
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
    Move();
}

void Enemy::Render()
{
    m_drawHelper.DrawShape(SHAPE_RECT, m_unitPos, m_unitSize, _RGBA{ 128, 25, 25, 0 });
}

void Enemy::MoveRestricter()
{
    if (m_rtBody.left <= 0 || m_rtBody.right >= W_WIDTH)
    {
        m_moveSpeed.x *= -1;
    }
}
