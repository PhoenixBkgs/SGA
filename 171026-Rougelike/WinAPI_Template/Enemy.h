#pragma once
#include "SpritesObject.h"

class Enemy : public SpritesObject
{
public:
    Enemy();
    ~Enemy();

    virtual void Update() override;
    virtual void Render() override;
};

