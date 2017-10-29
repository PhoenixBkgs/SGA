#pragma once
#include "SpritesObject.h"

class Item : public SpritesObject
{
public:
    Item();
    ~Item();

    virtual void Update() override;
    virtual void Render() override;
};

