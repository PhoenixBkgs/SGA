#pragma once
#include "GameObject.h"
#include "TileObject.h"

class MapObject : public GameObject
{
private:
public:
    MapObject();
    ~MapObject();

#pragma region GET
#pragma endregion
#pragma region SET
#pragma endregion


    void Start();
    virtual void Update() override;
    virtual void Render() override;
};

