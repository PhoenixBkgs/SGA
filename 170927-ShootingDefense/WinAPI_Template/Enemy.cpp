#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
    srand((int)time(NULL) * 73);

    m_LifeCount = rand() % 3 + 1;
    m_score = 4 - m_LifeCount;
    m_score *= m_score;
    m_score *= 100;

    m_unitSize.w = m_LifeCount * 20;
    m_unitSize.h = m_unitSize.w;

    m_moveSpeed.x = MOVE_SPEED;
    m_moveSpeed.y = 0.0f;

    int genDir = rand() % 1000;
    if (genDir > 500)
    {
        //  gen left
        m_unitPos.x = (double)m_unitSize.w + 1;
    }
    else
    {
        //  gen right
        m_unitPos.x = (double)(W_WIDTH - m_unitSize.w - 1);
        m_moveSpeed.x *= -1.0f;
    }
    m_unitPos.y = (double)(rand() % 400) + 100;

    SetBodyRect(m_unitPos, m_unitSize);
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
    Move();
    MoveRestricter();
}

void Enemy::Render()
{
    //m_drawHelper.DrawShape(SHAPE_RECT, m_unitPos, m_unitSize, _RGBA{ 128, 25, 25, 0 });
    Rectangle(g_hDC, m_rtBody.left, m_rtBody.top, m_rtBody.right, m_rtBody.bottom);
    FillRect(g_hDC, &m_rtBody, *m_bBrush);
}

void Enemy::MoveRestricter()
{
    if (m_rtBody.left <= 0 && m_moveSpeed.x < 0)
    {
        m_moveSpeed.x *= -1;
    }
    else if (m_rtBody.right >= W_WIDTH && m_moveSpeed.x > 0)
    {
        m_moveSpeed.x *= -1;
    }
}
