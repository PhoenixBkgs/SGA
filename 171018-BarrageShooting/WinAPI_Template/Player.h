#pragma once
#include "GameObject.h"

#define PLAYER_SPEED    10.0f
#define PLAYER_WIDTH    60
#define PLAYER_HEIGHT   70

#define PLAYER_INIT_POS_X   (W_WIDTH * 0.5f)
#define PLAYER_INIT_POS_Y   (W_HEIGHT * 0.5f)

class Player : public GameObject
{
public:
    Player();
    Player(string szTagName);
    ~Player();
};

