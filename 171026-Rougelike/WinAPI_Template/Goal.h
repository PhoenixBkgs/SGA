#pragma once
#include "SpritesObject.h"

class Goal : public SpritesObject
{
public:
    Goal();
    ~Goal();

    virtual void Update() override;
    virtual void Render() override;
};

