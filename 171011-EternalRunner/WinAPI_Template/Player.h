#pragma once
#include "GameNode.h"
#include "GameUnit.h"
#include "ImageKomastar.h"

#define GRAVITY 9.8f

class Obstacle;

class Player : public GameUnit
{
private:
    double      m_currDownForce;

public:
    ImageKomastar* m_pImg;
    vector<Obstacle>* m_vecObstacles;

    Player();
    ~Player();

    void Start();
    void Update();
    void Render();
};

