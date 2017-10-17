#include "stdafx.h"
#include "Target.h"
#include "Wind.h"

Target::Target()
    : m_pWind(NULL)
    , m_bIsShoot(false)
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
    m_dHitBoxPos = m_dPos;
    m_dHitBoxPos.y += 300;
    m_rtHitBox = g_pDrawHelper->MakeRect(m_dHitBoxPos, m_nSize);

    m_dAimPos = g_pGeoHelper->GetCenterPointWindow();
    m_nAimSize = UnitSize{ 300, 300};
    m_rtAim = g_pDrawHelper->MakeRect(m_dAimPos, m_nAimSize);

    m_nWindIdicatorX = UnitSize{ 0, 0 };
    m_nWindIdicatorY = UnitSize{ 0, 0 };
}

void Target::Update()
{
    if (m_pWind != NULL)
    {
        m_nWindIdicatorX = UnitSize{ (int)(m_pWind->GetSpeed3D().x * 500.0f), 5 };
        m_nWindIdicatorY = UnitSize{ 5, (int)(m_pWind->GetSpeed3D().y * 500.0f) };
    }
}

void Target::AimRender()
{
    if (m_bIsShoot)
    {

    }
    else
    {
        g_pDrawHelper->DrawEllipse(g_hDC, m_rtAim);
        RECT rt = g_pDrawHelper->MakeRectSizeMode(m_dAimPos, m_nAimSize, 0.6f);
        g_pDrawHelper->DrawEllipse(g_hDC, rt);
        rt = g_pDrawHelper->MakeRectSizeMode(m_dAimPos, m_nAimSize, 0.2f);
        g_pDrawHelper->DrawEllipse(g_hDC, rt);
        rt = g_pDrawHelper->MakeRectSizeMode(m_dAimPos, m_nAimSize, 0.01f);
        g_pDrawHelper->DrawEllipse(g_hDC, rt);
        //  WIND INDICATOR
        rt = g_pDrawHelper->MakeRect(UnitPos{ m_dAimPos.x + m_nWindIdicatorX.w, m_dAimPos.y }, m_nWindIdicatorX);
        g_pDrawHelper->DrawRect(g_hDC, rt);
        rt = g_pDrawHelper->MakeRect(UnitPos{ m_dAimPos.x, m_dAimPos.y + m_nWindIdicatorY.h }, m_nWindIdicatorY);
        g_pDrawHelper->DrawRect(g_hDC, rt);
    }
}