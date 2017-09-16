#pragma once

#include "ShapeDrawer.h"

#define PLAYER_WIDTH 40
#define PLAYER_HEIGHT 40

class Player : public ShapeDrawer
{
//=======================================================
//  VARIABLES
private:
    RECT m_playerRect;
    int m_moveSpeed;

public:


//=======================================================
//  FUNCTIONS
private:
public:
    Player();
    ~Player();

    void Setup();
    void Update();
    void Render(HDC hdc);

    RECT GetPlayerRect() { return m_playerRect; }
    POINT GetPlayerPos();
};

