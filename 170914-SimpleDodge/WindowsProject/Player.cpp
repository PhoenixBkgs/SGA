#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::SetWindowSize(int Width, int Height)
{
    m_windowSize.push_back(Width);
    m_windowSize.push_back(Height);
}

void Player::SetPlayerSize(int Width, int Height)
{
    m_playerSize.push_back(Width);
    m_playerSize.push_back(Height);
}

void Player::SetPlayerSpawnPos(int PosX, int PosY)
{
    m_playerSpawnPos.push_back(PosX);
    m_playerSpawnPos.push_back(PosY);
}

bool Player::ValidatePlayerInfo()
{
    bool IsValidate = true;
    if (m_playerSize.size() < 2)
    {
        //  INVALID
        IsValidate = false;
    }
    if (m_playerSpawnPos.size() < 2)
    {
        //  INVALID
        IsValidate = false;
    }
    if (m_windowSize.size() < 2)
    {
        //  INVALID
        IsValidate = false;
    }
    return IsValidate;
}

void Player::CreatePlayer()
{
    m_player.left = m_playerSpawnPos[0];
    m_player.right = m_playerSpawnPos[0] + m_playerSize[0];
    m_player.top = m_playerSpawnPos[1];
    m_player.bottom = m_playerSpawnPos[1] + m_playerSize[1];
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
