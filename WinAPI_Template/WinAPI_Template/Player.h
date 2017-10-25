#pragma once
#include "SpritesObject.h"

class Player : public SpritesObject
{
    //  vars
private:
    GameObject  m_gameObj;
    int         m_playerState;

    double      m_dJumpPower;
    bool        m_bIsJump;
    double      m_gravity;
public:
    Player();
    ~Player();

    virtual void Update() override;
    virtual void Render() override;
    
    void PlayerController();
};