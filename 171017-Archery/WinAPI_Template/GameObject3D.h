#pragma once
#include "GameObject.h"

class GameObject3D : public GameObject
{
protected:
    UnitPos3D       m_dPos3D;
    UnitSpeed3D     m_dSpeed3D;
public:
    GameObject3D();
    ~GameObject3D();

#pragma region GET
    UnitPos3D   GetUnitPos3D() { return m_dPos3D; }
    UnitSpeed3D GetSpeed3D() { return m_dSpeed3D; }
#pragma endregion

#pragma region SET
    void    SetPos3D(UnitPos3D Pos3D) { m_dPos3D = Pos3D; }
    void    SetSpeed3D(UnitSpeed3D Speed3D) { m_dSpeed3D = Speed3D; }
#pragma endregion

    void    Move3D();
};

