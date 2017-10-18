#pragma once
#include "GameObject.h"

class MapObject : public GameObject
{
private:

public:
    MapObject();
    ~MapObject();

    void Setup();
    void Update();
    void Render();
};

