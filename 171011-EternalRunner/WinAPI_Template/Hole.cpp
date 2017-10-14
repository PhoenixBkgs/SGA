#include "stdafx.h"
#include "Hole.h"


Hole::Hole()
{
    m_unitSize.w = 0;
    m_unitSize.h = FLOOR;
    Start();
}


Hole::~Hole()
{
}

void Hole::Start()
{
    int holeType = rand() % 1;
    switch (holeType)
    {
    case 0:
        m_unitSize.w += HOLE_PCS_WIDTH;
    default:
        m_unitSize.w += HOLE_PCS_WIDTH;
        break;
    }
}

void Hole::Update()
{
    Move();
    m_rtBody.top = W_HEIGHT - FLOOR;
    m_rtBody.bottom = W_HEIGHT;
}

void Hole::Render()
{
    RenderBodyRect(g_hDC);
    if (m_bBrush != NULL)
    {
        FillRect(g_hDC, &m_rtBody, *m_bBrush);
    }
    if (m_img != NULL)
    {
        m_img->Render(g_hDC, m_rtBody.left, m_rtBody.top, m_unitSize.w, m_unitSize.h, 0, 0, m_img->GetWidth(), m_img->GetHeight(), 255);
    }
}
