#pragma once
#include "GameObject.h"

class ProjectileObject : public GameObject
{
private:
    UnitPos     m_genPos;
    UnitPos     m_destPos;

public:
    ProjectileObject();
    ~ProjectileObject();
};

