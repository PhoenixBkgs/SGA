#pragma once
#include "SpritesObject.h"

class Bullet : public SpritesObject
{
private:
    double  m_dDmg;
public:
    Bullet();
    Bullet(string szTagName);
    ~Bullet();

    void    SetDamage(double Damage) { m_dDmg = Damage; }
    double  GetDamage() { return m_dDmg; }

    virtual void Update() override;

};