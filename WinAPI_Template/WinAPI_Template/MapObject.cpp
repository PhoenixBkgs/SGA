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
    if (m_dPos.y > W_HEIGHT + GetBodySize().h * 0.5)
    {
        m_dPos.y = W_HEIGHT * 0.5f;
    }
}

void MapObject::Render()
{
    m_imgBody->Render(g_hDC, (int)(m_dPos.x - GetBodySize().w * 0.5f), (int)(m_dPos.y - GetBodySize().h * 1.5f), GetBodySize().w, GetBodySize().h);
    m_imgBody->Render(g_hDC, (int)(m_dPos.x - GetBodySize().w * 0.5f), (int)(m_dPos.y - GetBodySize().h * 0.5f), GetBodySize().w, GetBodySize().h);
    GameObject::Render();
}
