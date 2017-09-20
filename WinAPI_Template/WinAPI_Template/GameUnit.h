#pragma once
class GameUnit
{
//  VARS
public:
    RECT    m_rtBody;
    POINT   m_ptMoveDir;
    int     m_LifeCount;
    HBRUSH  m_bBrush;

//  FUNCS
public:
    GameUnit();
    GameUnit(POINT Position, HBRUSH Brush);       //  1x1 RECT
    GameUnit(POINT Position, POINT Size, HBRUSH Brush, int Life);
    ~GameUnit();

    RECT* GetBodyRect() { return &m_rtBody; }
    void SetBodyRect(POINT GenPos);
    void SetBodyRect(POINT GenPos, POINT BodySize);

    void SetMoveDir(POINT Pt) { m_ptMoveDir = Pt; }
    POINT GetMoveDir() { return m_ptMoveDir; }

    int GetLifeCount() { return m_LifeCount; }
    void SetLifeCount(int Life) { m_LifeCount = Life; }
    
    void SetBrush(HBRUSH Brush) { m_bBrush = Brush; }

    void Move();
    void Destroy();
    bool Collider(RECT* TargetRect);
};

