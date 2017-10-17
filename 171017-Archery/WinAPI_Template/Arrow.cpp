#include "stdafx.h"
#include "Arrow.h"
#include "Player.h"
#include "Wind.h"
#include "Target.h"

Arrow::Arrow()
    : m_pWind(NULL)
    , m_dSpeedMirrorArrow(UnitSpeed{ 0.0f, 0.0f })
    , m_brushDestPoint(NULL)
    , m_nArrowCount(ARROW_MAX)
{
    m_brushDestPoint = new HBRUSH;
    *m_brushDestPoint = CreateSolidBrush(RGB(0, 0, 0));
}

Arrow::~Arrow()
{
    delete m_brushDestPoint;
}

void Arrow::Setup()
{
    m_dPos = m_pPlayer->GetPos();
    m_dSpeed = UnitSpeed{ 0.0f, 0.0f };
    m_dSpeedMirrorArrow = UnitSpeed{ 0.0f, 0.0f };
    m_dSpeed3D = UnitSpeed3D{ 0.0f, 0.0f, 0.0f };
    m_nSize = UnitSize{ ARROW_LENGTH, ARROW_THICK };
    m_rtBody = g_pDrawHelper->MakeRect(m_dPos, m_nSize);
    m_dHitBoxPos = m_dPos;
    m_dHitBoxPos.y += 300.0f;
    m_isAlive = true;
    m_rtHitBox = g_pDrawHelper->MakeRect(m_dHitBoxPos, m_nSize);
    Arrive();
}

void Arrow::Update()
{
    Move();
    m_dHitBoxPos.x = m_dPos.x;
    m_dHitBoxPos.y += m_dSpeed3D.z;

    m_rtHitBox = g_pDrawHelper->MakeRect(m_dHitBoxPos, m_nSize);
    
    if (m_isShoot)
    {
        if (m_pWind != NULL)
        {
            m_dSpeed3D.x += m_pWind->GetSpeed3D().x;
            m_dSpeed3D.y += m_pWind->GetSpeed3D().y;
            m_dSpeed3D.z += m_pWind->GetSpeed3D().z;
        }
        m_dSpeed.x = m_dSpeed3D.x;
        m_dSpeed.y = m_dSpeed3D.y;
    }

    RECT rt;
    if (m_pTarget != NULL)
    {
        m_pTarget->SetShoot(m_isShoot);
        if (IntersectRect(&rt, &m_rtBody, &m_pTarget->GetBodyRect()))
        {
            if (IntersectRect(&rt, &m_rtHitBox, &m_pTarget->GetHitBoxRect()))
            {
                m_dDestPos.x = W_WIDTH * 0.5f - (m_pTarget->GetPos().y - m_dPos.y);
                m_dDestPos.y = W_HEIGHT * 0.5f - (m_pTarget->GetHitBoxPos().y - m_dHitBoxPos.y);
                double dist = g_pGeoHelper->GetDistance(m_dDestPos, UnitPos{ W_WIDTH * 0.5f, W_HEIGHT * 0.5f });
                if (m_isAlive)
                {
                    if (dist < 50.0f)
                    {
                        m_pPlayer->SumScore(100);
                    }
                    else if (dist < 100.0f)
                    {
                        m_pPlayer->SumScore(50);
                    }
                    else if (dist < 150.0f)
                    {
                        m_pPlayer->SumScore(25);
                    }
                    else
                    {
                        m_pPlayer->SumScore(10);
                    }
                }
                m_dSpeed.x = 0.0f;
                m_dSpeed.y = 0.0f;
                m_dSpeed3D.x = 0.0f;
                m_dSpeed3D.y = 0.0f;
                m_dSpeed3D.z = 0.0f;
                m_isShoot = false;
                m_isAlive = false;
            }
        }
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
    g_pDrawHelper->DrawBoxLine2D(m_rtHitBox, 3, _RGBA{ 255, 0, 0, 0 });
}

void Arrow::DestPointRender()
{
    RECT tempRt = g_pDrawHelper->MakeRect(m_dDestPos, UnitSize{ 10, 10 });
    if (m_brushDestPoint != NULL)
    {
        FillRect(g_hDC, &tempRt, *m_brushDestPoint);
    }
}
