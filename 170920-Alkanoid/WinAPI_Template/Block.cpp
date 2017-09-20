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
    m_bBrush = CreateSolidBrush(RGB(100, 100, 100));
    SetBodyRect(POINT{ 0, 0 }, POINT{ BLOCK_WIDTH, BLOCK_HEIGHT });
}

void Block::Render()
{
    Draw(SHAPE_RECT, false);
    FillRect(g_hDC, &m_rtBody, m_bBrush);
}

void Block::Update()
{
    //  NO MOVE
    SetColor(m_LifeCount, 10, 10);
}
