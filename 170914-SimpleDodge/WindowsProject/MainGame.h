#pragma once

#include "GameNode.h"

class MainGame : public GameNode
{
private:
    Player m_player;

public:
    MainGame();
    ~MainGame();


    void Update() override;
    // GameNode을(를) 통해 상속됨
    virtual void Render(HDC hdc) override;
};

