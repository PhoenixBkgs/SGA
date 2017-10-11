#pragma once
#include "GameNode.h"
#include "GameUnit.h"
#include "ImageKomastar.h"

#define GRAVITY 9.8f

class Player : public GameUnit
{
private:

public:
    ImageKomastar* m_pImg;

    Player();
    ~Player();

    void Start();
    void Update();
    void Render();
};

