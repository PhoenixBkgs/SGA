#include "stdafx.h"
#include "Player.h"


Player::Player()
{
    Setup();
}


Player::~Player()
{
}

void Player::Setup()
{
    int playerSpawnPosX = (int)(WIN_WIDTH * 0.5);
    int playerSpawnPosY = (int)(WIN_WIDTH * 0.5);
    int playerHalfWidth = (int)(PLAYER_WIDTH * 0.5);
    int playerHalfHeight = (int)(PLAYER_HEIGHT * 0.5);
    m_playerRect = { playerSpawnPosX - playerHalfWidth, playerSpawnPosY - playerHalfHeight, playerSpawnPosX + playerHalfWidth, playerSpawnPosY + playerHalfHeight };
    m_moveSpeed = 5;
}

void Player::Update()
{
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        m_playerRect.left -= m_moveSpeed;
        m_playerRect.right -= m_moveSpeed;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        m_playerRect.left += m_moveSpeed;
        m_playerRect.right += m_moveSpeed;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        m_playerRect.top -= m_moveSpeed;
        m_playerRect.bottom -= m_moveSpeed;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        m_playerRect.top += m_moveSpeed;
        m_playerRect.bottom += m_moveSpeed;
    }
}

void Player::Render(HDC hdc)
{
    Rectangle(hdc, m_playerRect.left, m_playerRect.top, m_playerRect.right, m_playerRect.bottom);
}
