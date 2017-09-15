#pragma once

using namespace std;

class Player
{
private:
    RECT m_player;
    bool m_isAlive = true;
    vector<int> m_windowSize;
    vector<int> m_playerSize;
    vector<int> m_playerSpawnPos;

public:
    Player();
    ~Player();
    
    const int m_playerSpeed = 10;

    void SetWindowSize(int Width, int Height);
    void SetPlayerSize(int Width, int Height);
    void SetPlayerSpawnPos(int PosX, int PosY);

    bool ValidatePlayerInfo();

    void CreatePlayer();
    void DrawPlayer(HDC hdc);
    void MovePlayer(int xPosMove);
    RECT GetPlayerRect();
    bool GetPlayerAliveFlag();
    void SetPlayerAliveFlag(bool AliveFlag);
};