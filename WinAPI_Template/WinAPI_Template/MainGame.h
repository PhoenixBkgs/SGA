#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:

//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    void Reset();

    void LoadAllResources();
    void LoadImageResources();
    void LoadSoundResources();
};