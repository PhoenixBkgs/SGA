#pragma once
#include "SceneObject.h"

class SpritesObject;
class LobbyScene : public SceneObject
{
private:
    SpritesObject*      m_bgImg;
    SpritesObject*      m_pPlayerTypeA;
    SpritesObject*      m_pPlayerTypeC;
    string              m_szSelectPlayer;
public:
    LobbyScene(E_GAME_STATE* State);
    ~LobbyScene();

#pragma region GET
    string      GetPlayerSelect() { return m_szSelectPlayer; }
#pragma endregion

#pragma region SET
    void        SetPlayerSelect(string Select) { m_szSelectPlayer = Select; }
#pragma endregion



    virtual void Update() override;
    virtual void Render() override;

    // SceneObject을(를) 통해 상속됨
    virtual void Setup() override;
    virtual void LoadImageResources() override;
    virtual void DeleteScene() override;
};

