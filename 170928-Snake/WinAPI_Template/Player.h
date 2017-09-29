#pragma once
#include "GameNode.h"
#include "GameUnit.h"
#include "Geometry2DKomastar.h"

#define UNIT_SIZE 40
#define MIN_SPEED 5.0f
#define MAX_SPEED 15.0f

class Player : public GameUnit
{
    //  VARS
private:
    Geometry2DKomastar m_geoHelper;

    E_UNIT_TYPE m_type;
    Player* m_pForwardPlayer;
    Player* m_pBackwardPlayer;

    double m_moveDirAngle;
    double m_moveSpeed;

public:
    //  FUNCS
private:

public:
    Player();
    Player(HBRUSH* Brush);
    Player(UnitPos Position, HBRUSH * Brush);
    ~Player();

    void Start();
    void Update();
    void Render();

    void MoveTo(UnitPos Pos);

    void SetForwardPlayer(Player* ForwardPlayer) { m_pForwardPlayer = ForwardPlayer; }
    void SumAngle(double Angle) { m_moveDirAngle += Angle; }
    void SetType(E_UNIT_TYPE Type) { m_type = Type; }
    void SetMoveSpeed(double Speed) { m_moveSpeed = Speed; }
    void SetDirAngle(double Angle) { m_moveDirAngle = Angle; }

    double GetDirAngle() { return m_moveDirAngle; }
    double GetMoveSpeed() { return m_moveSpeed; }
private:
    void MoveToAngle();     //  HEAD ONLY
    void MoveToLinear();    //  BODY, TAIL ONLY
    void ValidateAngle();
    void CalcVectorSpeed();
};

