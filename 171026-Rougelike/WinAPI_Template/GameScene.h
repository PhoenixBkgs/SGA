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

    Player*             m_pPlayer;

public:
    GameScene(E_GAME_STATE* State);
    ~GameScene();


    virtual void Update() override;
    virtual void Render() override;

    // SceneObject을(를) 통해 상속됨
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void DeleteScene() override;
};

