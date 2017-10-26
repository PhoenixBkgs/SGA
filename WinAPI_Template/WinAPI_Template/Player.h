#pragma once
#include "SpritesObject.h"

class Player : public SpritesObject
{
    //  vars
private:
    SpritesObject* m_pPad;
    GameObject  m_gameObj;
    int         m_playerState;

    double      m_dJumpPower;
    bool        m_bIsJump;
    double      m_gravity;
public:
    Player();
    ~Player();

    void SetPad(SpritesObject* Pad) { m_pPad = Pad; }

    virtual void Update() override;
    virtual void Render() override;
    
    void PlayerController();
};