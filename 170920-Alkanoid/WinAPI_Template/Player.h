#pragma once
#include "GameNode.h"
#include "GameUnit.h"

#define PLAYER_SPEED    5.0f

class Player : public GameNode, public GameUnit
{
private:

public:
    Player();
    ~Player();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
};

