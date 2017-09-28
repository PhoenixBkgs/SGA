#pragma once
#include "GameNode.h"
#include "GameUnit.h"
#include "ImageKomastar.h"


class Player : public GameUnit
{
private:

public:
    Player();
    ~Player();

    void Start();
    void Update();
    void Render();
};

