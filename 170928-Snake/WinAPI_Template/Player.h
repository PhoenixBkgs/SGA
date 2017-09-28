#pragma once
#include "GameNode.h"
#include "GameUnit.h"
#include "Geometry2DKomastar.h"

#define UNIT_SIZE 20

class Player : public GameUnit
{
    //  VARS
private:
    Geometry2DKomastar m_geoHelper;

    E_UNIT_TYPE m_type;
    Player* m_pForwardPlayer;
    Player* m_pBackwardPlayer;

    UnitPos m_unitPos;
    double m_moveDirAngle;
    double m_moveSpeed;

public:
    //  FUNCS
private:

public:
    Player();
    ~Player();

    void Start();
    void Update();
    void Render();

    void Move() override;

private:
    void MoveToAngle();     //  HEAD ONLY
    void MoveToLinear();    //  BODY, TAIL ONLY
};

