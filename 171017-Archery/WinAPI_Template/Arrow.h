#pragma once
#include "GameObject3D.h"

#define ARROW_LENGTH 200
#define ARROW_THICK 10

class Player;
class Wind;
class Arrow : public GameObject3D
{
private:
    //  MUTUAL REF
    Player*             m_pPlayer;
    Wind*               m_pWind;
    E_VIEW_MODE         m_viewMode;
    bool                m_isShoot;

public:
    Arrow();
    ~Arrow();

    void Setup();
    void Update();
    void Render();

#pragma region GET

#pragma endregion

#pragma region SET
    void SetPlayer(Player* Player) { m_pPlayer = Player; }
    void SetWind(Wind* Wind) { m_pWind = Wind; }
    void Shoot() { m_isShoot = true; }
    void Arrive() { m_isShoot = false; }
#pragma endregion

};