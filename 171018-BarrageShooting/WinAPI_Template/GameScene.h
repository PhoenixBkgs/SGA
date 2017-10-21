#pragma once
#include "SceneObject.h"

class MapObject;
class Player;
class Enemy;

class GameScene : public SceneObject
{
private:
    MapObject*              m_pMap;
    Player*                 m_pPlayer;
    Enemy*                  m_pEnemy;
public:
    GameScene(E_GAME_STATE* State);
    ~GameScene();

    virtual void Update() override;

    // SceneObject��(��) ���� ��ӵ�
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void AddComponentsToScene() override;
    virtual void DeleteScene() override;
};

