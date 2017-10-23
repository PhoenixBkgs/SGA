#include "stdafx.h"
#include "Item.h"


Item::Item()
{
}


Item::~Item()
{
}

void Item::Update()
{
    SpritesObject::Update();
    m_nLife--;
    if (m_dPos.x < m_nSize.w * 0.5f ||
        m_dPos.x > W_WIDTH - m_nSize.w * 0.5f)
    {
        m_dSpeed.x = -m_dSpeed.x;
    }
    if (m_dPos.y < m_nSize.h * 0.5f ||
        m_dPos.y > W_HEIGHT - m_nSize.h * 0.5f)
    {
        m_dSpeed.y = -m_dSpeed.y;
    }

    if (m_nLife < 0)
    {
        m_isAlive = false;
    }
}

void Item::Render()
{
    SpritesObject::Render();
}

Item Item::GenItem(UnitPos GenPos, UnitSize Size)
{
    Item genItem;
    genItem.SetBodyImg(g_pImgManager->FindImage("item"));
    genItem.SetBodyPos(GenPos);
    genItem.SetBodySize(Size);
    genItem.SetBodyRect(g_pDrawHelper->MakeRect(GenPos, Size));
    genItem.SetupForSprites(1, 1);
    genItem.SetHBoxMargin({ 0, 0, 0, 0 });
    genItem.SetHBox();
    double xSpeed = (double)(rand() % 5 + 1);
    double ySpeed = (double)(rand() % 5 + 1);
    xSpeed -= 2.5f;
    genItem.SetBodySpeed({ xSpeed, ySpeed });
    genItem.SetScore(10);
    genItem.SetLife(500);
    genItem.SetAlive();

    return genItem;
}
