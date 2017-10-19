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
}

void MapObject::Render()
{
    m_imgBody->Render(g_hDC, (int)(m_dPos.x - GetSize().w * 0.5f), (int)(m_dPos.y - GetSize().h * 0.5f), GetSize().w, GetSize().h);
    GameObject::Render();
}
