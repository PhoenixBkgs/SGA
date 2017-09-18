#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:

public:

//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;
};

