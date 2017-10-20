#pragma once
#include "SpritesObject.h"

class Bullet : public SpritesObject
{
private:
    double  m_dDmg;
    UnitPos m_dStartPos;
    UnitPos m_dDestPos;
public:
    double  m_t;
    Bullet();
    Bullet(string szTagName);
    ~Bullet();

    void    SetDamage(double Damage) { m_dDmg = Damage; }
    void    SetStartPos(UnitPos Pos) { m_dStartPos = Pos; }
    void    SetDestPos(UnitPos Pos) { m_dDestPos = Pos; }
    double  GetDamage() { return m_dDmg; }
    UnitPos GetStartPos() { return m_dStartPos; }
    UnitPos GetDestPos() { return m_dDestPos; }
    double  GetT() { return m_t; }

    virtual void Update() override;

};