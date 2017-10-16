#pragma once
#include "GameNode.h"
#include "GameObject.h"
#include "ImageObject.h"

#define GRAVITY 9.8f

class Player : public GameObject
{
private:

public:
    ImageObject* m_pImg;

    Player();
    ~Player();

    void Start();
    void Update();
    void Render();
};

