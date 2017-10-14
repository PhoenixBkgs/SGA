#include "stdafx.h"
#include "Obstacle.h"
#include "Player.h"

Obstacle::Obstacle()
    : m_pImg(NULL)
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
    if (m_pImg != NULL)
    {
        m_pImg->Render(g_hDC, 
                        m_rtBody.left,  m_rtBody.top, 
                        m_unitSize.w,   m_unitSize.h, 
                        0, 0, 
                        m_pImg->GetWidth(), m_pImg->GetHeight(), 
                        255);
    }
}
