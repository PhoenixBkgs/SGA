#pragma once

#include "GameNode.h"
#include "Player.h"
#include "Draw2DKomastar.h"
#include "Geometry2DKomastar.h"
#include "Physics2DKomastar.h"
#include "ImageKomastar.h"

#include "cCard.h"

struct Card
{
    ImageKomastar* ImageFront;
    ImageKomastar* ImageBack;
    RECT ImageRect;
    bool IsOpen;
    bool IsFinished;
    int cardId;
};

struct tagImage
{
    ImageKomastar* ImageFront;
    ImageKomastar* ImageBack;
    int cId;
};

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    Draw2DKomastar      m_drawHelper;
    Geometry2DKomastar  m_geoHelper;
    Physics2DKomastar   m_physicsHelper;

    vector<tagImage> m_vecStImages;
    vector<cCard>    m_vecCards;
    cCard* m_prevCard;

    bool m_hasInsight;
    bool m_isPlaying;
    bool m_isEnd;
    int m_showIdx1;
    int m_showIdx2;
    int m_showIdx3;
    int m_showIdx4;
    int m_showSleepCnt;
    int m_showCount;
    int m_finishCount;
    int m_prevUid;

public:
    int m_clickCount;
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

