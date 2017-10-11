#pragma once
#include "GameUnit.h"
#include "ImageKomastar.h"

class Player;

class Obstacle : public GameUnit
{
public:
    ImageKomastar* m_pImg;
    Player* m_playerRef;

    Obstacle();
    ~Obstacle();

    void Start();
    void Update();
    void Render();
};

