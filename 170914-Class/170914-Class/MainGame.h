#pragma once

#include "Player.h"
#include "Monster.h"
#include "Shop.h"
#include "Inventory.h"
#include "Item.h"

enum LOCATION
{
    L_TOWN, L_SHOP, L_INVEN, L_DUNGEON, L_END
};

class MainGame
{
private:
    LOCATION m_curLoc;  //  current location
    LOCATION m_preLoc;  //  previous location

    Player* m_player;
    Monster* m_monster;
    Inventory* m_inven;

    void InTown();
    void InShop();
    void OpenInven();
    void InDungeon();


public:
    MainGame();
    ~MainGame();

    bool MainPlay();
};

