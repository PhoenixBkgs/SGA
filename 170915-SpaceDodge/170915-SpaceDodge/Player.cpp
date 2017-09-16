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
    //  플레이어 크기와 위치 초기화
    int playerSpawnPosX = (int)(WIN_WIDTH * 0.5);
    int playerSpawnPosY = (int)(WIN_WIDTH * 0.5);
    int playerHalfWidth = (int)(PLAYER_WIDTH * 0.5);
    int playerHalfHeight = (int)(PLAYER_HEIGHT * 0.5);
    
    m_playerRect.left = playerSpawnPosX - playerHalfWidth;
    m_playerRect.right = playerSpawnPosX + playerHalfWidth;
    m_playerRect.top = playerSpawnPosY - playerHalfHeight;
    m_playerRect.bottom = playerSpawnPosY + playerHalfHeight;
    
    //  플레이어 이동 속도 초기화
    m_moveSpeed = 5;
}

void Player::Update()
{
    //  방향키 입력 처리
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
    //  플레이어 그리기
    DrawRectangle(hdc, m_playerRect);
}

POINT Player::GetPlayerPos()
{
    POINT ptPlayer;

    ptPlayer.x = m_playerRect.left + (LONG)(PLAYER_WIDTH * 0.5);
    ptPlayer.y = m_playerRect.top + (LONG)(PLAYER_HEIGHT * 0.5);

    return ptPlayer;
}
