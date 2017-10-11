#include "stdafx.h"
#include "Item.h"


Item::Item() :
    m_imgAlpha(255)
{
}


Item::~Item()
{
}

void Item::Start()
{
}

void Item::Update()
{
    Move();
}

void Item::Render()
{
    m_itemImg->SpritesRender(g_hDC, m_rtBody, m_imgAlpha);
}
