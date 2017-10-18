#pragma once
#include "SpritesObject.h"

#define PLAYER_SPEED    10.0f
#define PLAYER_WIDTH    60
#define PLAYER_HEIGHT   70

#define PLAYER_INIT_POS_X   (W_WIDTH * 0.5f)
#define PLAYER_INIT_POS_Y   (W_HEIGHT - 100.0f)

class Player : public SpritesObject
{
public:
    Player();
    Player(string szTagName);
    ~Player();

    virtual void Update() override;
    virtual void Render() override;
};

