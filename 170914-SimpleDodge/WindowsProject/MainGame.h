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
    // GameNode��(��) ���� ��ӵ�
    virtual void Render(HDC hdc) override;
};

