#pragma once
#include "EnumState.h"
#include "DrawHelper.h"

class GameUnit
{
//  VARS
public:
    RECT        m_rtBody;
    UnitSpeed   m_ptMoveDir;
    int         m_LifeCount;
    HBRUSH      m_bBrush;
    bool        m_isRender;
    UnitPos     m_ptPos;
    UnitSize    m_unitSize;

//  FUNCS
public:
    GameUnit();
    GameUnit(UnitPos Position, HBRUSH Brush);       //  1x1 RECT
    GameUnit(UnitPos Position, UnitSize Size, HBRUSH Brush, int Life);
    ~GameUnit();

    RECT* GetBodyRect() { return &m_rtBody; }
    void SetBodyRect(UnitPos GenPos);
    void SetBodyRect(UnitPos GenPos, UnitSize BodySize);

    void SetPosition(UnitPos Pos);
    UnitPos GetPosition();

    void SetMoveDir(UnitSpeed Pt) { m_ptMoveDir = Pt; }
    UnitSpeed GetMoveDir() { return m_ptMoveDir; }
    void SetMoveDirReverse(E_REFLECT_DIR Dir);

    int GetLifeCount() { return m_LifeCount; }
    void SetLifeCount(int Life) { m_LifeCount = Life; }
    
    void SetBrush(HBRUSH Brush) { m_bBrush = Brush; }
    void SetColor(int R, int G, int B);

    void Move();
    void Stop();
    void Draw(E_SHAPE Shape, bool DrawForce);
    void Destroy();
    bool Collider(RECT* TargetRect);
};

