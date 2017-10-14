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
#ifdef _DEBUG
    m_drawHelper.DrawLine2D(m_unitPos, UnitPos{ m_unitPos.x + m_moveSpeed.x, m_unitPos.y + m_moveSpeed.y }, 3, _RGBA{255, 0, 0, 0});
#endif // _DEBUG

}
