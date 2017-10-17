#include "stdafx.h"
#include "Target.h"


Target::Target()
{
}


Target::~Target()
{
}

void Target::Setup()
{
    m_nSize.w = TARGET_WIDTH;
    m_nSize.h = TARGET_HEIGHT;
    m_dPos.x = W_WIDTH - m_nSize.w;
    m_dPos.y = (W_HEIGHT - 150) - 300;
    m_rtBody = g_pDrawHelper->MakeRect(m_dPos, m_nSize);
    m_rtHitBox = m_rtBody;
    m_rtHitBox.top += 300;
    m_rtHitBox.bottom += 300;
}

void Target::Update()
{
}