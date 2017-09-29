#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Draw2DKomastar.h"
#include "Geometry2DKomastar.h"
#include "Physics2DKomastar.h"
#include "ImageKomastar.h"

#define GENERATION_DELAY    50
#define HANDLE_TICK         10.0f
#define MAX_AI_WAIT         100

struct tagItem
{
    RECT    rtBody;
    int     addition;
    double  accel;
    E_ITEM_TYPE itemType;
    UnitPos Pos;
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
    bool    m_isAutoPlaying;
    bool    m_isReal;
    int     m_generationDelay;
    int     m_prevGameScore;
    int     m_gameScore;
    int     m_itemCount;
    int     m_aiWaitCount;
    double  m_targetAngle;

    vector<Player>  m_vecPlayer;
    vector<tagItem> m_vecItem;

    HBRUSH m_brushPlayer;
    HBRUSH m_brushItem1;
    HBRUSH m_brushItem2;
    HBRUSH m_brushItem3;
//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    void UserInterfaceRender();

    void PlayerController();
    void SystemController();

    void GenItem();
};

