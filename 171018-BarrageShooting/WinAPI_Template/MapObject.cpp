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
    GameObject::Render();
    m_imgBody->Render(g_hDC, m_dPos.x - GetSize().w * 0.5f, m_dPos.y - GetSize().h * 0.5f, GetSize().w, GetSize().h);
}
