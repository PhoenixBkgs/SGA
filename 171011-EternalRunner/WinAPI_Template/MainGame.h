#pragma once
#include "GameNode.h"
#include "ImageKomastar.h"
#include "Player.h"
#include "Obstacle.h"

#define BG_WIDTH 6600
#define BG_HEIGHT 675

#define OBS_GEN_DELAY   100

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    ImageKomastar*      m_bgImg;        //  Background image 6600 x 675
    ImageKomastar*      m_img;          //  Player sprites image 108 x 140 x 8 x 2

    Player              m_player;
    vector<Obstacle>    m_vecObstacle;

    double              m_bgPosX;
    double              m_bgPosX2;
    double              m_runSpeed;

    int                 m_obsGenDelayCount;
//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;

    void GenerateObstacle();
};