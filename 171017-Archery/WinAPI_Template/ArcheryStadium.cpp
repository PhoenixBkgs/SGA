#include "stdafx.h"
#include "ArcheryStadium.h"


ArcheryStadium::ArcheryStadium()
{
}


ArcheryStadium::~ArcheryStadium()
{
}

void ArcheryStadium::Setup()
{
    m_nSize.w = W_WIDTH;
    m_nSize.h = 300;
    m_rtBody = g_pDrawHelper->MakeRect(m_dPos, m_nSize);
    m_rtHitBox = g_pDrawHelper->MakeRect(m_dPos, UnitSize{ W_WIDTH, W_HEIGHT });
}

void ArcheryStadium::Render()
{
    g_pDrawHelper->DrawBoxLine2D(m_rtBody, 10, _RGBA{ 0, 0, 0, 0 });
    g_pDrawHelper->DrawBoxLine2D(m_rtHitBox, 10, _RGBA{ 0, 0, 0, 0 });


}
