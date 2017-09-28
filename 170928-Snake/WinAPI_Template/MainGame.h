#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Draw2DKomastar.h"
#include "Geometry2DKomastar.h"
#include "Physics2DKomastar.h"
#include "ImageKomastar.h"

#define GENERATION_DELAY    50

struct tagItem
{
    RECT    rtBody;
    int     addition;
    double  slower;
};

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    Draw2DKomastar      m_drawHelper;
    Geometry2DKomastar  m_geoHelper;
    Physics2DKomastar   m_physicsHelper;

    bool    m_isPlaying;
    int     m_generationDelay;

    vector<Player>  m_vecPlayer;
    vector<tagItem> m_vecItem;
//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;

    void PlayerController();
    void SystemController();

    void GenItem();
};

