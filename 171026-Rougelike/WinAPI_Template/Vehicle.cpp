#include "stdafx.h"
#include "Vehicle.h"


Vehicle::Vehicle()
{
    m_destDC = g_pImgManager->FindImage("map-buffer");
}


Vehicle::~Vehicle()
{
}

void Vehicle::Setup()
{
    g_pTimerManager->AddOnOffTimer(m_szTagName, { 0.0f, 0.0f }, 0.05f, 1.0f);
}

void Vehicle::Update()
{
    m_dPos.x = m_startPos.x + m_destPos.x;
    m_dPos.y = m_startPos.y + m_destPos.y;

    if (g_pTimerManager->TickOnOffTimer(m_szTagName))
    {
        m_dSpeed.x = VEHICLE_SPEED;
        //m_startPos.x += VEHICLE_SPEED;
    }
    else
    {
        m_dSpeed.x = -VEHICLE_SPEED;
        //m_startPos.x += -VEHICLE_SPEED;
    }

    m_startPos.x += m_dSpeed.x;
    m_rtBody = g_pDrawHelper->MakeRect(m_dPos, m_nSize);
    SetHBox();
    //SpritesObject::Update();
}

void Vehicle::Render()
{
    if (m_isVisible == true)
    {
        if (m_imgBody != NULL)
        {
            m_imgBody->SpritesRender(m_destDC->GetMemDC(), m_rtBody, m_currFrameX, m_currFrameY, m_dAlpha);
        }
    }

    GameObject::Render();
}
