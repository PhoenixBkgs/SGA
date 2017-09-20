#include "stdafx.h"
#include "Block.h"


Block::Block()
{
    Start();
}


Block::~Block()
{
}

void Block::Start()
{
    m_isRender = true;
    m_LifeCount = 1;
    m_R = m_LifeCount * 50;
    m_bBrush = CreateSolidBrush(RGB(200, 100, 100));
    SetBodyRect(UnitPos{ 0.0f, 0.0f }, UnitSize{ BLOCK_WIDTH, BLOCK_HEIGHT });
}

void Block::Render()
{
    Draw(SHAPE_RECT, true);
    FillRect(g_hDC, &m_rtBody, m_bBrush);
}

void Block::Update()
{
    Move();
}
