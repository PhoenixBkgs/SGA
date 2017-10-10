#pragma once
#include "GameNode.h"
#include "GameUnit.h"
#include "ImageKomastar.h"

#define IDLE_FRAME 10

class Player : public GameUnit
{
private:
public:
    ImageKomastar* m_pImg;
    int     m_idleSpriteIdx;
    int     m_idleDelay;

    Player();
    ~Player();

    void Start();
    void Update();
    void Render();
};

