#pragma once
#include "SpritesObject.h"

class Trap : public SpritesObject
{
public:
    Trap();
    ~Trap();

    virtual void Update() override;
    virtual void Render() override;
};

