#pragma once
#include "EnumState.h"
#include "GameNode.h"

#include "ImageKomastar.h"
#include "Draw2DKomastar.h"
#include "Geometry2DKomastar.h"

#include "UserInterface.h"

#include "Player.h"
#include "Obstacle.h"
#include "Item.h"
#include "Hole.h"

#define BG_WIDTH 6600
#define BG_HEIGHT 675

#define OBJ_GEN_OFFSET  1000.0f
#define OBS_GEN_DELAY   200
#define ITEM_GEN_DELAY  15
#define HOLE_GEN_LIMITER  500

#define GAME_SPEED 10.0f
#define INIT_GAME_TIMER 500
#define INIT_SHOW_TIMER 50
#define INIT_COUNT_DOWN 3

#define COUNT_DOWN_RECT_MARGIN 400
class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    Draw2DKomastar      m_drawHelper;
    Geometry2DKomastar  m_geoHelper;
    UserInterface       m_uiHelper;

    E_GAME_STATE        m_currGameState;
    ImageKomastar*      m_bgImg;            //  Background image 6600 x 675px
    ImageKomastar*      m_playerImg;        //  Player sprites image 108 x 140 x 8 x 2px
    ImageKomastar*      m_playerImmortalImg;
    ImageKomastar*      m_scoreItemImg;     //  Item score image 50 x 50 x 8 x 1px
    ImageKomastar*      m_magnetItemImg;    //  Item magnet image 50 x 50 x 8 x 1px
    ImageKomastar*      m_immortalItemImg;  //  Item immortal image 50 x 50 x 8 x 1px
    ImageKomastar*      m_giantItemImg;     //  Item giant image 50 x 50 x 8 x 1px
    ImageKomastar*      m_heartImg;
    ImageKomastar*      m_splashBgImg;
    ImageKomastar*      m_splashBladeImg;
    ImageKomastar*      m_landBlockImg;
    ImageKomastar*      m_holeBlockImg;
    ImageKomastar*      m_bkBg;
    ImageKomastar*      m_flagImg;
    ImageKomastar*      m_slideTestImg;

    vector<ImageKomastar*> m_vecSpritesImgs;
    Player              m_player;
    vector<Obstacle>    m_vecObstacles;
    vector<Item>        m_vecItems;
    vector<Hole>        m_vecHoles;

    double              m_bgPosX;
    double              m_bgPosX2;
    double              m_runSpeed;
    double              m_PosX;
    double              m_progress;

    int                 m_gameTimer;
    int                 m_gameLevel;
    int                 m_showTimer;
    int                 m_showCount;
    int                 m_obsGenDelayCount;
    int                 m_itemGenDelayCount;
    int                 m_holeGenLimitCount;

    bool                m_isCounting;
    bool                m_isShowSlide;

    HBRUSH              m_holeBrush;
    RECT                m_countDownRt;
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
    void ShowTimerReset();
    void LoadImages();

    void Play();
    void DrawPlayer();
    void DrawObstacles();
    void DrawItems();
    void DrawHoles();

    void GenerateObstacle();
    void GenerateItem();
    void GenerateHole();
    void SpritesRefresh();

    void CountDown();
    void ClearScreen(string szText);

    void SystemControl();
    void PlayerControl();
};