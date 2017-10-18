#pragma once
#include "SpritesObject.h"

class Bullet : public SpritesObject
{
public:
    Bullet();
    Bullet(string szTagName);
    ~Bullet();

    virtual void Update() override;
};