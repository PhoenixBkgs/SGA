#pragma once
#include "SpritesObject.h"

class Bullet : public SpritesObject
{
public:
    Bullet();
    Bullet(string szTagName);
    ~Bullet();

    void Setup();

    virtual void Update() override;
};