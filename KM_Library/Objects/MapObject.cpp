#include "stdafx.h"
#include "MapObject.h"


MapObject::MapObject()
{
    GameObject::GameObject();
}

MapObject::~MapObject()
{
}

void MapObject::Update()
{
    m_dPos.y += 5.0f;
    if (m_dPos.y > W_HEIGHT + GetSize().h * 0.5)
    {
        m_dPos.y = W_HEIGHT * 0.5f;
    }
}

void MapObject::Render()
{
    m_imgBody->Render(g_hDC, (int)(m_dPos.x - GetSize().w * 0.5f), (int)(m_dPos.y - GetSize().h * 1.5f), GetSize().w, GetSize().h);
    m_imgBody->Render(g_hDC, (int)(m_dPos.x - GetSize().w * 0.5f), (int)(m_dPos.y - GetSize().h * 0.5f), GetSize().w, GetSize().h);
    GameObject::Render();
}
