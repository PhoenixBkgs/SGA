#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}

Bullet::Bullet(string szTagName)
{
    m_szTagName = szTagName;
    SetBodyImgAuto();
    m_dDmg = -1.0f;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
    SpritesObject::Update();
    SetFrameX(0);

    UnitPos pos = GetPos();
    if (pos.x < 0 ||
        pos.x > W_WIDTH ||
        pos.y < 0 ||
        pos.y > W_HEIGHT)
    {
        SetDead();
    }
}

void Bullet::Render()
{
    SpritesObject::Render();
}

vector<Bullet> Bullet::SingleShot(UnitPos Pos, double Angle)
{
    Bullet SingleShot;
    SingleShot.SetTagName(m_szTagName);
    SingleShot.SetBodyImg(g_pImgManager->FindImage("bullet"));
    SingleShot.SetupForSprites(2, 2);
    SingleShot.SetBodyPos(Pos);
    SingleShot.SetBodySize({ 10, 10 });
    SingleShot.m_dDmg = -5.0f;
    SingleShot.SetBodySpeed(g_pGeoHelper->GetCoordFromAngle(Angle, 10.0f));
    SingleShot.SetBodyRect(g_pDrawHelper->MakeRect(Pos, { 10, 10 }));
    SingleShot.SetHBoxMargin({ 0, 0, 0, 0 });
    SingleShot.SetHBox();

    return vector<Bullet>{SingleShot};
}

vector<Bullet> Bullet::Magnum(UnitPos Pos, double Angle)
{
    Bullet Magnum;
    Magnum.SetTagName(m_szTagName);
    Magnum.SetBodyImg(g_pImgManager->FindImage("bullet"));
    Magnum.SetupForSprites(2, 2);
    Magnum.SetBodyPos(Pos);
    Magnum.SetBodySize({ 20, 20 });
    Magnum.m_dDmg = -25.0f;
    Magnum.SetBodySpeed(g_pGeoHelper->GetCoordFromAngle(Angle, 30.0f));
    Magnum.SetBodyRect(g_pDrawHelper->MakeRect(Pos, { 10, 10 }));
    Magnum.SetHBoxMargin({ 0, 0, 0, 0 });
    Magnum.SetHBox();

    return vector<Bullet>{Magnum};
}

vector<Bullet> Bullet::Buckshot(UnitPos Pos, double Angle)
{
    vector<Bullet> vecBuckshot;
    Bullet Buckshot;
    Buckshot.SetTagName(m_szTagName);
    Buckshot.SetBodyImg(g_pImgManager->FindImage("bullet"));
    Buckshot.SetupForSprites(2, 2);
    Buckshot.SetBodyPos(Pos);
    Buckshot.SetBodySize({ 20, 20 });
    Buckshot.m_dDmg = -5.0f;
    Buckshot.SetBodySpeed(g_pGeoHelper->GetCoordFromAngle(Angle, 15.0f));
    Buckshot.SetBodyRect(g_pDrawHelper->MakeRect(Pos, { 10, 10 }));
    Buckshot.SetHBoxMargin({ 0, 0, 0, 0 });
    Buckshot.SetHBox();
    vecBuckshot.push_back(Buckshot);

    Buckshot.SetBodySpeed(g_pGeoHelper->GetCoordFromAngle(Angle + 5.0f, 15.0f));
    vecBuckshot.push_back(Buckshot);

    Buckshot.SetBodySpeed(g_pGeoHelper->GetCoordFromAngle(Angle - 5.0f, 15.0f));
    vecBuckshot.push_back(Buckshot);
    
    return vecBuckshot;
}

vector<Bullet> Bullet::BarrageHD(UnitPos Pos, double Angle)
{
    vector<Bullet> vecBarrage;
    Bullet BarrageHD;
    BarrageHD.SetTagName(m_szTagName);
    BarrageHD.SetBodyImg(g_pImgManager->FindImage("bullet"));
    BarrageHD.SetupForSprites(2, 2);
    BarrageHD.SetBodyPos(Pos);
    BarrageHD.SetBodySize({ 20, 20 });
    BarrageHD.m_dDmg = -2.0f;
    BarrageHD.SetBodyRect(g_pDrawHelper->MakeRect(Pos, { 5, 5 }));
    BarrageHD.SetHBoxMargin({ 0, 0, 0, 0 });
    BarrageHD.SetHBox();
    double dAngle = -7.5f;
    for (int i = 0; i < 15; i++)
    {
        BarrageHD.SetBodySpeed(g_pGeoHelper->GetCoordFromAngle(Angle + dAngle + (double)i, 5.0f));
        vecBarrage.push_back(BarrageHD);
    }

    return vecBarrage;
}