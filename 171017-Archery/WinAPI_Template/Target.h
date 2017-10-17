#pragma once
#include "GameObject.h"

#define TARGET_WIDTH    25
#define TARGET_HEIGHT   200

class Target : public GameObject
{
public:
    Target();
    ~Target();

    void Setup();
    void Update();
};

