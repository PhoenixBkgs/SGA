#include "stdafx.h"
#include "Player.h"
#include "Arrow.h"

Player::Player()
    : m_dPowerStep(POWER_STEP)
    , m_isPullingTrigger(false)
    , m_nScore(0)
{
    m_brushGauge = new HBRUSH;
    *m_brushGauge = CreateSolidBrush(RGB(120, 50, 50));
}


Player::~Player()
{
    delete m_brushGauge;
}

void Player::Setup()
{
    m_nSize.w = PLAYER_WIDTH;
    m_nSize.h = PLAYER_HEIGHT;
    m_dPos.x = PLAYER_WIDTH * 0.5f;
    m_dPos.y = 600.0f - PLAYER_HEIGHT;
    m_rtBody = g_pDrawHelper->MakeRect(m_dPos, m_nSize);
    m_rtHitBox = m_rtBody;
    m_rtHitBox.top += 300;
    m_rtHitBox.bottom += 300;
    m_dPowerGauge = 0.0f;
    m_isPullingTrigger = false;
    m_rtGauge = g_pDrawHelper->MakeRect(UnitPos{ W_WIDTH * 0.5f, W_HEIGHT - 75 }, UnitSize{ 200, 50 });
    int nGaugeMargin = 3;
    m_rtGaugeFill = { m_rtGauge.left + nGaugeMargin, m_rtGauge.top + nGaugeMargin, m_rtGaugeFill.left + 1, m_rtGauge.bottom - nGaugeMargin };
}

void Player::Update()
{
    m_dPowerGauge -= 0.5f;
    m_dPowerGauge = m_dPowerGauge > 200.0f ? 200.0f : m_dPowerGauge;
    m_dPowerGauge = m_dPowerGauge < 0.0f ? 0.0f : m_dPowerGauge;

    int nGaugeMargin = 3;
    m_rtGaugeFill = { m_rtGauge.left + nGaugeMargin, m_rtGauge.top + nGaugeMargin
                    , m_rtGaugeFill.left + (int)m_dPowerGauge, m_rtGauge.bottom - nGaugeMargin };
}

void Player::PullTrigger()
{
    m_isPullingTrigger = true;
    m_dPowerGauge += 2.0f;
}

void Player::Shoot()
{
    if (m_isPullingTrigger == true)
    {
        UnitPos relativePos;
        UnitPos centerPos = g_pGeoHelper->GetCenterPointWindow();
        relativePos.x = (double)g_ptMouse.x - centerPos.x;
        relativePos.y = (double)g_ptMouse.y - centerPos.y;
        double xSpeed = m_dPowerGauge * 0.1f;      //  x speed
        double ySpeed = relativePos.x;
        double zSpeed = relativePos.y;
        double powerLimiter = 100.0f;
        ySpeed = ySpeed > powerLimiter ? powerLimiter : ySpeed;
        zSpeed = zSpeed > powerLimiter ? powerLimiter : zSpeed;

        ySpeed *= 0.01f;
        zSpeed *= 0.01f;

        m_pArrow->SetSpeed3D(UnitSpeed3D{ xSpeed, ySpeed, zSpeed });
        m_pArrow->Shoot();
        m_pArrow->SumArrowCount(-1);
    }
    m_isPullingTrigger = false;
}

void Player::GaugeRender()
{
    g_pDrawHelper->DrawRect(g_hDC, m_rtGauge);
    if (m_isPullingTrigger == true)
    {
        g_pDrawHelper->DrawRect(g_hDC, m_rtGaugeFill, m_brushGauge);
    }
}
