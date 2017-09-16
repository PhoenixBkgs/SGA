#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Bullet.h"

class MainGame : public GameNode
{
private:
    bool m_isPlaying;
    int m_gameLvl;

    Player m_player;
    vector<Bullet> m_bullet;

public:
    MainGame();
    ~MainGame();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;
};

