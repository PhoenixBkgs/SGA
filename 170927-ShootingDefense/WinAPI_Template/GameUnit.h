#pragma once
#include "Draw2DKomastar.h"

class GameUnit
{
//  VARS
public:
    Draw2DKomastar  m_drawHelper;

    RECT            m_rtBody;
    UnitPos         m_unitPos;
    UnitSize        m_unitSize;
    UnitSpeed       m_moveSpeed;
    
    HBRUSH          m_bBrush;

    int             m_LifeCount;

//  FUNCS
public:
    GameUnit();
    GameUnit(UnitPos Position, HBRUSH Brush);
    GameUnit(UnitPos Position, UnitSize Size, HBRUSH Brush, int Life);
    ~GameUnit();

    RECT* GetBodyRect() { return &m_rtBody; }
    void SetBodyRect(UnitPos GenPos, UnitSize BodySize);
    
    void UpdateBodyPos(UnitPos GenPos);

    UnitPos GetPosition() { return m_unitPos; }
    void SetPosition(UnitPos Position) { m_unitPos = Position; }

    UnitSize GetSize() { return m_unitSize; }
    void SetSize(UnitSize Size) { m_unitSize = Size; }

    UnitSpeed GetMoveSpeed() { return m_moveSpeed; }
    void SetMoveSpeed(UnitSpeed Speed) { m_moveSpeed = Speed; }

    int GetLifeCount() { return m_LifeCount; }
    void SetLifeCount(int Life) { m_LifeCount = Life; }
    
    HBRUSH GetBrush() { return m_bBrush; }
    void SetBrush(HBRUSH Brush) { m_bBrush = Brush; }


    void SetColor(int R, int G, int B);

    void Move();
    void Draw(bool DrawForce);
    void Destroy();
};

