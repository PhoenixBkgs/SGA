#pragma once
#include "SceneObject.h"

class MapObject;
class Player;
class Enemy;

class GameScene : public SceneObject
{
private:
    string                  m_szPlayerSelect;
    MapObject*              m_pMap;
    Player*                 m_pPlayer;
    Enemy*                  m_pEnemy;
public:
    GameScene(E_GAME_STATE* State);
    ~GameScene();

#pragma region GET
    string    GetSelectPlayer() { return m_szPlayerSelect; }
#pragma endregion
#pragma region SET
    void    SetPlayerSelect(string szString) { m_szPlayerSelect = szString; }
    void    SetPlayerImg(string szString);
#pragma endregion


    virtual void Update() override;
    virtual void Render() override;

    // SceneObject을(를) 통해 상속됨
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void DeleteScene() override;
};

