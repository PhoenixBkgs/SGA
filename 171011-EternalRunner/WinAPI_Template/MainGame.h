#pragma once
#include "GameNode.h"
#include "Player.h"
#include "ImageKomastar.h"

#define BG_WIDTH 6600
#define BG_HEIGHT 675

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    ImageKomastar* m_bgImg;     //  6600 x 675
    ImageKomastar* m_img;

    Player m_player;

    double              m_bgPosX;
    double              m_bgPosX2;
    double              m_runSpeed;
//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
};