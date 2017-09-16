#pragma once
#define PLAYER_WIDTH 40
#define PLAYER_HEIGHT 40

class Player
{
private:
    RECT m_playerRect;
    int m_moveSpeed;

public:
    Player();
    ~Player();

    void Setup();
    void Update();
    void Render(HDC hdc);

    RECT GetPlayerRect() { return m_playerRect; }
};

