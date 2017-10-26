#pragma once
#include "GameObject.h"

class TileObject : public GameObject
{
private:

public:
    TileObject();
    ~TileObject();

    virtual void Update() override;
    virtual void Render(HDC hdc);
};