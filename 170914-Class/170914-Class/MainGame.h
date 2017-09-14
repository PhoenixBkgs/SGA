#pragma once

#include "Player.h"
#include "Monster.h"
#include "Shop.h"
#include "Inventory.h"
#include "Item.h"

enum LOCATION
{
    L_TOWN, L_SHOP, L_INVEN, L_DUNGEON
};

class MainGame
{
private:
    Player m_player;
    Monster m_monster;

public:
    MainGame();
    ~MainGame();
};

