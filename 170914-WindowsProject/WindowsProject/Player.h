#pragma once

#define PLAYER_WIDTH 10
#define PLAYER_HEIGHT 10

class Player
{
private:
    RECT m_player;
    bool m_isAlive = true;

public:
    Player();
    ~Player();
    
    const int m_playerSpeed = 10;

    void CreatePlayer();
    void DrawPlayer(HDC hdc);
    void MovePlayer(int xPosMove);
    RECT GetPlayerRect();
    bool GetPlayerAliveFlag();
    void SetPlayerAliveFlag(bool AliveFlag);
};