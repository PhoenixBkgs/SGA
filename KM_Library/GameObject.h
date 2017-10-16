#pragma once
#include "DrawHelper.h"

class GameObject
{
//  VARS
public:
    DrawHelper  m_drawHelper;

    RECT            m_rtBody;
    RECT            m_hitBox;
    UnitPos         m_unitPos;
    UnitSize        m_unitSize;
    UnitSpeed       m_moveSpeed;
    
    HBRUSH          m_bBrush;

    int             m_LifeCount;
    bool            m_isImmortal;
    bool            m_isActive;
    bool            m_isMovable;

//  FUNCS
public:
    GameObject();
    GameObject(UnitPos Position, HBRUSH Brush);
    GameObject(UnitPos Position, UnitSize Size, HBRUSH Brush, int Life);
    ~GameObject();

    RECT* GetBodyRect() { return &m_rtBody; }
    void SetBodyRect(UnitPos GenPos, UnitSize BodySize);
    RECT SetBodyRect(UnitPos GenPos, UnitSize BodySize, int Margin);
    
    void UpdateBodyPos(UnitPos GenPos);

    UnitPos GetPosition() { return m_unitPos; }
    void SetPosition(UnitPos Position) { m_unitPos = Position; }

    UnitSize GetSize() { return m_unitSize; }
    void SetSize(UnitSize Size) { m_unitSize = Size; }

    UnitSpeed GetMoveSpeed() { return m_moveSpeed; }
    void SetMoveSpeed(UnitSpeed Speed) { m_moveSpeed = Speed; }

    int GetLifeCount() { return m_LifeCount; }
    void SetLifeCount(int Life) { m_LifeCount = Life; }
    void SumLifeCount(int Life) { m_LifeCount += Life; }
    
    HBRUSH GetBrush() { return m_bBrush; }
    void SetBrush(HBRUSH Brush) { m_bBrush = Brush; }

    void SetColor(int R, int G, int B);

    void Activate() { m_isActive = true; }
    void Deactivate() { m_isActive = false; }
    bool IsActive() { return m_isActive; }

    void SetMovable(bool Movable) { m_isMovable = Movable; }
    bool GetMovable() { return m_isMovable; }

    void Move();
    void Destroy();

    //  COLLIDER
    void BoxCollider2D(vector<GameObject> MultipleUnit);
};

