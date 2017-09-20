#include "stdafx.h"
#include "Ball.h"


Ball::Ball()
{
    Start();
}


Ball::~Ball()
{
}

void Ball::Start()
{
    SetBodyRect(UnitPos{ 0, 0 }, UnitSize{ BALL_SIZE, BALL_SIZE });
}

void Ball::Render()
{
    Draw(SHAPE_ELLIPSE, true);
    Ellipse(g_hDC, m_rtBody.left, m_rtBody.top, m_rtBody.right, m_rtBody.bottom);
    if (BALL_SIZE > (m_rtBody.right - m_rtBody.left))
    {
        g_pLog4K->WriteLog(EL_ALERT, "INVALID BALL SIZE");
    }
}

void Ball::Update()
{
    Move();
}
