#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_player = new Player;
    m_monster = new Monster;
    m_inven = new Inventory;

    m_curLoc = L_TOWN;
    m_preLoc = L_TOWN;
}


MainGame::~MainGame()
{
}

bool MainGame::MainPlay()
{
    system("cls");

    switch (m_curLoc)
    {
    case L_TOWN:
        InTown();
        break;
    case L_SHOP:
        InShop();
        break;
    case L_INVEN:
        OpenInven();
        break;
    case L_DUNGEON:
        InDungeon();
        break;

    default:
        break;
    }
}

void MainGame::InTown()
{
    int nSelect;

    cout << "===============================================" << endl;
    cout << "=              WELCOME TO UP TOWN             =" << endl;
    cout << "===============================================" << endl;
    cout << "1. 상점행" << endl;
    cout << "2. 인벤행" << endl;
    cout << "3. 던전행" << endl;
    cout << "4. 현실행" << endl;
    cin >> nSelect;

    m_curLoc = (LOCATION)nSelect;

    switch (nSelect)
    {
    case L_INVEN:
        m_preLoc = m_curLoc;
        break;
    case L_END:
        break;
    default:
        break;
    }
}

void MainGame::InShop()
{
    int nSelect;

    cout << "===============================================" << endl;
    cout << "=              WELCOME TO SHOP                =" << endl;
    cout << "===============================================" << endl;
    cout << "1. 마을행" << endl;
    cout << "2. 인벤행" << endl;
    cin >> nSelect;
}

void MainGame::OpenInven()
{
    int nSelect;

    cout << "===============================================" << endl;
    cout << "=           THIS IS YOUR INVENTORY            =" << endl;
    cout << "===============================================" << endl;
    cout << "1. 수고행" << endl;
    cin >> nSelect;
}

void MainGame::InDungeon()
{
    int nSelect;

    cout << "===============================================" << endl;
    cout << "=        YOU ARE IN DANGEROUS DUNGEON         =" << endl;
    cout << "===============================================" << endl;
    cout << "1. 마을행" << endl;
    cout << "2. 인벤행" << endl;
    cin >> nSelect;
}

