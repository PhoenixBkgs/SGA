#pragma once
#include "SpritesObject.h"

class Bullet : public SpritesObject
{
private:
    E_WEAPON_TYPE       m_weaponType;
    double              m_dDmg;
    UnitPos             m_dStartPos;
    UnitPos             m_dDestPos;
public:
    float               m_t;

public:
    Bullet();
    Bullet(string szTagName);
    ~Bullet();

#pragma region GET
    double  GetDamage() { return m_dDmg; }
    UnitPos GetStartPos() { return m_dStartPos; }
    UnitPos GetDestPos() { return m_dDestPos; }
#pragma endregion

#pragma region SET
    void    SetDamage(double Damage) { m_dDmg = Damage; }
    void    SetStartPos(UnitPos Pos) { m_dStartPos = Pos; }
    void    SetDestPos(UnitPos Pos) { m_dDestPos = Pos; }
    void    SetBulletType(E_WEAPON_TYPE Type) { m_weaponType = Type; }
#pragma endregion

    virtual void Update() override;
    virtual void Render() override;

#pragma region GEN_BULLETS
    vector<Bullet>      SingleShot(UnitPos Pos, double Angle);
    vector<Bullet>      Magnum(UnitPos Pos, double Angle);
    vector<Bullet>      Buckshot(UnitPos Pos, double Angle);
    vector<Bullet>      BarrageHD(UnitPos Pos, double Angle);
#pragma endregion
};