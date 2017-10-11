#include "stdafx.h"
#include "Obstacle.h"
#include "Player.h"

Obstacle::Obstacle()
{
}


Obstacle::~Obstacle()
{
}

void Obstacle::Start()
{

}

void Obstacle::Update()
{
    Move();
}

void Obstacle::Render()
{
    Rectangle(g_hDC, m_rtBody.left, m_rtBody.top, m_rtBody.right, m_rtBody.bottom);
}
