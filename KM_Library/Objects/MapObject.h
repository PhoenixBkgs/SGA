#pragma once
#include "GameObject.h"

class MapObject : public GameObject
{
private:
    RECT    m_rtMapArea;

public:
    MapObject();
    ~MapObject();

#pragma region GET
    RECT    GetMapArea() { return m_rtMapArea; }
#pragma endregion

#pragma region SET
    void    SetMapArea(RECT Area) { m_rtMapArea = Area; }
#pragma endregion

    void Update();
    virtual void Render() override;
};

