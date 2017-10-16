#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
    : m_uId(-1)
    , m_szTagName("none")
    , m_imgBody(NULL)
    , m_dPos(UnitPos{ W_WIDTH * 0.5f, W_HEIGHT * 0.5f })
    , m_dSpeed(UnitPos{ 0.0f, 0.0f })
    , m_nSize(UnitSize{ 1, 1 })
    , m_isVisible(true)
    , m_isAlive(true)
    , m_dAlpha(0.0f)
    , m_dAngle(0.0f)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

void GameObject::Render()
{
}

void GameObject::Move()
{
}
