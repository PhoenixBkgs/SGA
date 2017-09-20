#pragma once
#include "GameNode.h"
#include "GameUnit.h"

class Player : public GameNode, GameUnit
{
private:

public:
    Player();
    ~Player();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
};

