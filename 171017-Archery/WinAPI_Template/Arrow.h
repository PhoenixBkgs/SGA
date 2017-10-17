#pragma once
#include "GameObject3D.h"

#define ARROW_LENGTH 100
#define ARROW_THICK 2
#define ARROW_MAX   10

class Player;
class Wind;
class Target;
class Arrow : public GameObject3D
{
private:
    //  MUTUAL REF
    int                 m_nArrowCount;
    Player*             m_pPlayer;
    Wind*               m_pWind;
    Target*             m_pTarget;
    E_VIEW_MODE         m_viewMode;
    bool                m_isShoot;
    UnitPos             m_dHitBoxPos;
    UnitSpeed           m_dSpeedMirrorArrow;
    HBRUSH*             m_brushDestPoint;
    UnitPos             m_dDestPos;
    int                 m_nScore;
public:
    Arrow();
    ~Arrow();

    void Setup();
    void Update();
    void Render();
    void DestPointRender();

#pragma region GET
    int     GetArrowRemain() { return m_nArrowCount; }
#pragma endregion

#pragma region SET
    void SetPlayer(Player* Player) { m_pPlayer = Player; }
    void SetWind(Wind* Wind) { m_pWind = Wind; }
    void SetTarget(Target* Target) { m_pTarget = Target; }
    void Shoot() { m_isShoot = true; }
    void Arrive() { m_isShoot = false; }
    void SumArrowCount(int SumNum) { m_nArrowCount += SumNum; }
#pragma endregion

};