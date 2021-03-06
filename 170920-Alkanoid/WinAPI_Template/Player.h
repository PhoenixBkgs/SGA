#pragma once
#include "GameNode.h"
#include "GameUnit.h"

#define PLAYER_SPEED    7.0f

class Player : public GameNode, public GameUnit
{
private:
    UnitPos m_barDestPos;
public:
    Player();
    ~Player();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
};

