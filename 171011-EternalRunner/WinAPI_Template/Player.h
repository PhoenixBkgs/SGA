#pragma once
#include "EnumState.h"
#include "GameUnit.h"
#include "ImageKomastar.h"
#include "Geometry2DKomastar.h"

#define PLAYER_WIDTH 108
#define PLAYER_HEIGHT 140

#define BUFF_DURING_TIME 200
#define GRAVITY 9.8f
#define INIT_DOWNFORCE 1.0f

#define FLOOR_POS_Y 550.0f

class Obstacle;
class Item;

class Player : public GameUnit
{
private:
    Geometry2DKomastar m_geoHelper;

    E_PLAYER_STATE  m_playerState;
    E_ITEM_TYPE     m_playerBuff;
    double          m_currDownForce;

    string          m_headUpMsg;
    int             m_score;
public:
    int             m_buffTimer;

    ImageKomastar* m_pImg;
    vector<Obstacle>* m_vecObstacles;
    vector<Item>* m_vecItems;

    Player();
    ~Player();

    void Start();
    void Update();
    void Render();

    E_PLAYER_STATE  GetPlayerState() { return m_playerState; }
    void            SetPlayerState(E_PLAYER_STATE State) { m_playerState = State; }

    E_ITEM_TYPE GetPlayerBuff() { return m_playerBuff; }
    void        SetPlayerBuff(E_ITEM_TYPE ItemType) { m_playerBuff = ItemType; }

    int     GetScore() { return m_score; }
    void    Reset();
};

