#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
    Bullet();
    Bullet(string szTagName);
    ~Bullet();

    void Setup();
};

