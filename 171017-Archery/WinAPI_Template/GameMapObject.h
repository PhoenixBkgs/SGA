#pragma once
#include "GameObject.h"

class GameMapObject : public GameObject
{
protected:

public:
    GameMapObject();
    ~GameMapObject();

    void Setup();
    void Update();
    void Render();
};

