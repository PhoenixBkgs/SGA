#include "stdafx.h"
#include "ShootingTarget.h"

ShootingTarget::ShootingTarget()
{
    Setup();
}


ShootingTarget::~ShootingTarget()
{
}

void ShootingTarget::Setup()
{
    m_isTargetUp = false;
}

void ShootingTarget::CreateTargetRect(HDC* hdc)
{
    POINT targetPos;
    int targetHalfWidth;
    int targetColor;
    switch (m_eTargetSize)
    {
    case TS_SMALL:
        targetHalfWidth = S_TARGET_WIDTH;
        targetColor = S_TARGET_COLOR;
        m_targetScore = 10;
        break;
    case TS_MEDIUM:
        targetHalfWidth = M_TARGET_WIDTH;
        targetColor = M_TARGEET_COLOR;
        m_targetScore = 5;
        break;
    case TS_LARGE:
        targetHalfWidth = L_TARGET_WIDTH;
        targetColor = L_TARGET_COLOR;
        m_targetScore = 1;
        break;
    }

    targetHalfWidth = (int)(targetHalfWidth * 0.5);
    m_targetRect = { m_targetPos.x - targetHalfWidth, m_targetPos.y + TARGET_THICK, m_targetPos.x + targetHalfWidth, m_targetPos.y };
    m_targetBrush = CreateSolidBrush(RGB(targetColor, targetColor, targetColor));
    FillRect(*hdc, &m_targetRect, m_targetBrush);
}

