#include "stdafx.h"
#include "Player.h"


Player::Player()
{
    Start();
}


Player::~Player()
{
}

void Player::Start()
{

}

void Player::Update()
{
    Move();
    UpdateBodyPos(m_unitPos);
}

void Player::Render()
{
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(g_hDC, hPen);
    SelectObject(g_hDC, *m_bBrush);
    Ellipse(g_hDC, m_rtBody.left, m_rtBody.top, m_rtBody.right, m_rtBody.bottom);
    DeleteObject(hPen);
    GetStockObject(WHITE_BRUSH);
}

void Player::Move()
{
    switch (m_type)
    {
    case UNIT_HEAD:
        MoveToAngle();
        break;
    case UNIT_BODY:
    case UNIT_TAIL:
        MoveToLinear();
        break;
    }
}

void Player::MoveToAngle()
{
    //  Get vector speed by calculation
    UnitSpeed moveVectorXY = m_geoHelper.GetCoordFromAngle(m_moveDirAngle, m_moveSpeed);
    //  Apply vector speed
    m_unitPos.x += moveVectorXY.x;
    m_unitPos.y += moveVectorXY.y;
}

void Player::MoveToLinear()
{
    //  Get position of forward node
    UnitPos followNodePos = m_pForwardPlayer->GetPosition();
    //  Apply position of current node
    m_unitPos = followNodePos;
}