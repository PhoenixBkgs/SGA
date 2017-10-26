#include "stdafx.h"
#include "TileObject.h"


TileObject::TileObject()
{
}


TileObject::~TileObject()
{
}

void TileObject::Update()
{
	GameObject::Update();
}

void TileObject::Render(HDC hdc)
{
    m_imgBody->TransRender(hdc, m_rtBody, 255);
}
