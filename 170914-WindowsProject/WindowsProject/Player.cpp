#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::CreatePlayer()
{
    int spawnPosX = 100;
    int spawnPosY = 630;
    m_player.left = spawnPosX;
    m_player.right = spawnPosX + PLAYER_WIDTH;
    m_player.top = spawnPosY;
    m_player.bottom = spawnPosY + PLAYER_HEIGHT;
}

void Player::DrawPlayer(HDC hdc)
{
    Rectangle(hdc, m_player.left, m_player.top, m_player.right, m_player.bottom);
}

void Player::MovePlayer(int xPosMove)
{
    m_player.left += xPosMove;
    m_player.right += xPosMove;
}

RECT Player::GetPlayerRect()
{
    return m_player;
}

bool Player::GetPlayerAliveFlag()
{
    return m_isAlive;
}

void Player::SetPlayerAliveFlag(bool AliveFlag)
{
    m_isAlive = AliveFlag;
}
