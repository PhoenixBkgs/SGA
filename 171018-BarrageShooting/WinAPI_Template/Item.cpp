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
