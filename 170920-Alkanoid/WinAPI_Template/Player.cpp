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
    m_isRender = true;
    SetBodyRect(UnitPos{ 0, 0 }, UnitSize{ 100, 40 });
    SetColor(0, 0, 0);
}

void Player::Update()
{
    Move();
}

void Player::Render()
{
    Draw(SHAPE_RECT, true);
}
