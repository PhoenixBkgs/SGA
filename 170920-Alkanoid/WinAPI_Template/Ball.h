#pragma once
#include "GameNode.h"
#include "GameUnit.h"

#define BALL_SIZE 20

class Ball : public GameNode, public GameUnit
{
public:
    Ball();
    ~Ball();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Render() override;
    void Update();
};

