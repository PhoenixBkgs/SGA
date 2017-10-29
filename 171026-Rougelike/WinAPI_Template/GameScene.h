#pragma once
#include "SceneObject.h"
#include "SpritesObject.h"
#include "Player.h"
#include "MapObject.h"

class GameScene : public SceneObject
{
private:
    vector<SpritesObject>  m_vecGameObjs;
    int                 m_nGameTimer;
	ImageObject*		m_pMinimap;
    MapObject           m_gameMap;
    UnitSize            m_nMapSize;
    Player*             m_pPlayer;

public:
    GameScene(E_GAME_STATE* State);
    ~GameScene();

    MapObject*      GetMapObj() { return &m_gameMap; }

    int     GetGameTimer() { return m_nGameTimer; }

    void    SetMapSize(UnitSize MapSize) { m_nMapSize = MapSize; }
    void    SetGameObjs(vector<SpritesObject> GameObjs) { m_vecGameObjs = GameObjs; }

    virtual void Update() override;
    virtual void Render() override;

    // SceneObject을(를) 통해 상속됨
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void DeleteScene() override;
};

