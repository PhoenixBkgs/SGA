#pragma once
#include "GameObject.h"

#define TARGET_WIDTH    25
#define TARGET_HEIGHT   200

class Wind;
class Target : public GameObject
{
private:
    Wind*           m_pWind;
    bool            m_bIsShoot;
    RECT            m_rtAim;
    UnitSize        m_nAimSize;
    UnitPos         m_dAimPos;
    UnitPos         m_dHitBoxPos;
    UnitSize        m_nWindIdicatorX;
    UnitSize        m_nWindIdicatorY;
public:
    Target();
    ~Target();

    UnitPos GetHitBoxPos() { return m_dHitBoxPos; }

    void SetWind(Wind* Wind) { m_pWind = Wind; }
    void SetShoot(bool IsShoot) { m_bIsShoot = IsShoot; }

    void Setup();
    void Update();
    void AimRender();
};

