#pragma once
#include "SceneObject.h"
#include "SpritesObject.h"
#include "Player.h"
#include "MapObject.h"

class GameScene : public SceneObject
{
private:
	ImageObject*		m_pMinimap;
    MapObject           m_gameMap;
    UnitSize            m_nMapSize;
    Player*             m_pPlayer;

public:
    GameScene(E_GAME_STATE* State);
    ~GameScene();

    MapObject*      GetMapObj() { return &m_gameMap; }


    void    SetMapSize(UnitSize MapSize) { m_nMapSize = MapSize; }

    virtual void Update() override;
    virtual void Render() override;

    // SceneObject을(를) 통해 상속됨
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void DeleteScene() override;
};

