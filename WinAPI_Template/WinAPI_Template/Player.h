#pragma once
#include "SpritesObject.h"

class Player : public SpritesObject
{
    //  vars
private:
    

public:
    Player();
    ~Player();

    virtual void Update() override;
    virtual void Render() override;
    
    void PlayerController();
};