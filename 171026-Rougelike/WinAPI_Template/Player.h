#pragma once
#include "SpritesObject.h"

#define JUMP_POWER	10.0f;

class TileObject;
class Player : public SpritesObject
{
    //  vars
private:
    E_PLAYER_BUFF   m_ePlayerBuff;

    vector<SpritesObject>* m_vecGameObjs;
	vector<TileObject>* m_vecTiles;
    GameObject  m_gameObj;
    int         m_playerState;

    double      m_dJumpPower;
    bool        m_bIsJump;
    double      m_gravity;

    bool        m_isClear;
    bool        m_isBoosterOn;
    double      m_dBoosterGauge;

public:
    Player();
    ~Player();

    bool    IsClear() { return m_isClear; }

    double  GetBoosterGauge() { return m_dBoosterGauge; }

	void    SetMapTiles(vector<TileObject>* MapTile) { m_vecTiles = MapTile; }
    void    SetGameObjs(vector<SpritesObject>* GameObjs) { m_vecGameObjs = GameObjs; }

    virtual void Update() override;
    virtual void Render() override;
    
    void PlayerController();
};