#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}

Player::Player(string szTagName)
{
    m_szTagName = szTagName;
    SetBodyImgAuto();
}

Player::~Player()
{
}