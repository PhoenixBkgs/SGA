#pragma once
#include "SpritesObject.h"

#define JUMP_POWER	25.0f;

class TileObject;
class Player : public SpritesObject
{
    //  vars
private:
	vector<TileObject>* m_vecTiles;
    GameObject  m_gameObj;
    int         m_playerState;

    double      m_dJumpPower;
    bool        m_bIsJump;
    double      m_gravity;
public:
    Player();
    ~Player();

	void SetMapTiles(vector<TileObject>* MapTile) { m_vecTiles = MapTile; }
    virtual void Update() override;
    virtual void Render() override;
    
    void PlayerController();
};