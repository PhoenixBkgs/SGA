#include "stdafx.h"
#include "Player.h"


Player::Player()
{
    Start();
}

Player::Player(HBRUSH * Brush)
{
    m_bBrush = Brush;
    Start();
}

Player::Player(UnitPos Position, HBRUSH * Brush)
{
    m_bBrush = Brush;
    Start();
}


Player::~Player()
{
}

void Player::Start()
{
    m_unitSize = { UNIT_SIZE , UNIT_SIZE };
    SetBodyRect(m_unitPos, m_unitSize);
}

void Player::Update()
{
    if (m_moveSpeed <= MIN_SPEED)
    {
        m_moveSpeed = MIN_SPEED;
    }

    if (m_moveSpeed >= MAX_SPEED)
    {
        m_moveSpeed = MAX_SPEED;
    }
    ValidateAngle();
    if (m_type == UNIT_HEAD)
    {
        MoveToAngle();
    }
    Move();
}

void Player::Render()
{
    HPEN hPen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
    SelectObject(g_hDC, hPen);
    SelectObject(g_hDC, *m_bBrush);
    Ellipse(g_hDC, m_rtBody.left, m_rtBody.top, m_rtBody.right, m_rtBody.bottom);
    DeleteObject(hPen);
    GetStockObject(WHITE_BRUSH);
}

void Player::MoveTo(UnitPos Pos)
{
    switch (m_type)
    {
    case UNIT_HEAD:
        MoveToAngle();
        break;
    case UNIT_BODY:
    case UNIT_TAIL:
        Move();
        break;
    }
}

void Player::MoveToAngle()
{
    //  Get vector speed by calculation
    UnitSpeed moveVectorXY = m_geoHelper.GetCoordFromAngle(m_moveDirAngle, m_moveSpeed);
    //  Apply vector speed
    m_moveSpeedXY = moveVectorXY;
}

void Player::MoveToLinear()
{
    //  Get position of forward node
    UnitPos followNodePos = m_pForwardPlayer->GetPosition();
    //  Apply position of current node
    m_unitPos = followNodePos;
}

void Player::ValidateAngle()
{
    while (true)
    {
        if (m_moveDirAngle > 360.0f)
        {
            m_moveDirAngle -= 360.0f;
        }
        else
        {
            break;
        }
    }
}

void Player::CalcVectorSpeed()
{
}
