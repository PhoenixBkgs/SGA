#include "stdafx.h"
#include "GameObject3D.h"


GameObject3D::GameObject3D()
    : m_dPos3D(UnitPos3D{ W_WIDTH * 0.5f, W_HEIGHT * 0.5f, 0.0f })
    , m_dSpeed3D(UnitSpeed3D{ 0.0f, 0.0f, 0.0f })
{
}


GameObject3D::~GameObject3D()
{
}

void GameObject3D::Move3D()
{
    m_dPos3D.x += m_dSpeed3D.x;
    m_dPos3D.y += m_dSpeed3D.y;
    m_dPos3D.z += m_dSpeed3D.z;
}
