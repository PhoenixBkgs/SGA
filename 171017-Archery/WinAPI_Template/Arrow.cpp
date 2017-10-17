#include "stdafx.h"
#include "Arrow.h"
#include "Player.h"
#include "Wind.h"

Arrow::Arrow()
    : m_pWind(NULL)
{
}

Arrow::~Arrow()
{
}

void Arrow::Setup()
{
    m_dPos = m_pPlayer->GetPos();
    m_nSize = UnitSize{ ARROW_LENGTH, ARROW_THICK };
    m_rtBody = g_pDrawHelper->MakeRect(m_dPos, m_nSize);
}

void Arrow::Update()
{
    if (m_isShoot)
    {
        if (m_pWind != NULL)
        {
            m_dSpeed3D.x += m_pWind->GetSpeed3D().x;
            m_dSpeed3D.y += m_pWind->GetSpeed3D().y;
            m_dSpeed3D.z += m_pWind->GetSpeed3D().z;
        }
        Move3D();
        m_dPos.x = m_dPos3D.x;
        m_dPos.y = m_dPos3D.y;
    }

    if (m_dPos.x > W_WIDTH)
    {
        m_isShoot = false;
    }
}

void Arrow::Render()
{
    double dMargin = 0.0f;
    switch (m_viewMode)
    {
    case VIEW_TOP:
        dMargin = 300.0f;
        break;
    case VIEW_FRONT:
        dMargin = 600.0f;
        break;
    }
    g_pDrawHelper->DrawBoxLine2D(m_rtBody, 3, _RGBA{ 255, 0, 0, 0 });
    RECT tempRt = m_rtBody;
    tempRt.top += 300.0f;
    tempRt.bottom += 300.0f;
    g_pDrawHelper->DrawBoxLine2D(tempRt, 3, _RGBA{ 255, 0, 0, 0 });
}
