#pragma once
#include "EnumState.h"
#include "GameNode.h"
#include "ImageKomastar.h"
#include "Player.h"
#include "Obstacle.h"
#include "Item.h"
#include "Draw2DKomastar.h"
#include "Geometry2DKomastar.h"
#include "UserInterface.h"

#define BG_WIDTH 6600
#define BG_HEIGHT 675

#define OBJ_GEN_OFFSET  1000.0f
#define OBS_GEN_DELAY   200
#define ITEM_GEN_DELAY  15

#define GAME_SPEED 20.0f

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
    ImageKomastar*      m_scoreItemImg;     //  Item score image 50 x 50 x 8 x 1px
    ImageKomastar*      m_magnetItemImg;    //  Item magnet image 50 x 50 x 8 x 1px
    ImageKomastar*      m_immortalItemImg;  //  Item immortal image 50 x 50 x 8 x 1px
    ImageKomastar*      m_giantItemImg;     //  Item giant image 50 x 50 x 8 x 1px
    ImageKomastar*      m_heartImg;
    ImageKomastar*      m_whiteImg;

    vector<ImageKomastar*> m_vecSpritesImgs;
    Player              m_player;
    vector<Obstacle>    m_vecObstacles;
    vector<Item>        m_vecItems;

    double              m_bgPosX;
    double              m_bgPosX2;
    double              m_runSpeed;

    int                 m_obsGenDelayCount;
    int                 m_itemGenDelayCount;

//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;

    void Play();
    void DrawPlayer();
    void DrawObstacles();
    void DrawItems();

    void GenerateObstacle();
    void GenerateItem();
    void SpritesRefresh();
};