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
    SetBodyRect(POINT{ 0, 0 }, POINT{ BALL_SIZE, BALL_SIZE });
}

void Ball::Render()
{
    Draw(SHAPE_ELLIPSE, true);
    Ellipse(g_hDC, m_rtBody.left, m_rtBody.top, m_rtBody.right, m_rtBody.bottom);
}

void Ball::Update()
{
    Move();
}
