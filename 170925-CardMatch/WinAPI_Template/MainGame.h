#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Draw2DKomastar.h"
#include "Geometry2DKomastar.h"
#include "Physics2DKomastar.h"
#include "ImageKomastar.h"

#define MAX_CARD 10
#define IMG_WIDTH 120
#define IMG_HEIGHT 200

struct Card
{
    ImageKomastar* ImageFront;
    ImageKomastar* ImageBack;
    RECT ImageRect;
    bool IsOpen;
    bool IsFinished;
    int cardId;
};

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    Draw2DKomastar      m_drawHelper;
    Geometry2DKomastar  m_geoHelper;
    Physics2DKomastar   m_physicsHelper;

    Card m_cards[MAX_CARD];
    string m_imageNames[MAX_CARD] = { "images/CardFront_Illidan.bmp",
                                      "images/CardFront_Tyrande.bmp",
                                      "images/CardFront-Liming.bmp",
                                      "images/CardFront_Jaina.bmp",
                                      "images/CardFront-Malfurion.bmp" };
public:
    int m_clickCount;
    int m_prevCardIdx = -1;
    int m_gameScore;
    bool m_isMatchFail;
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

