#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Bullet.h"
#include "UserInterface.h"

#define MAX_GAMELEVEL 50

enum E_GAMESTATE
{
    GS_LOADING = 0, GS_READY, GS_PLAYING, GS_PAUSE, GS_STAGECLEAR, GS_GAMEOVER
};

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    int m_gameLvl;
    int m_gameScore;
    int m_bulletRegenCounter;

    E_GAMESTATE m_eGameState;

    UserInterface m_ui;
    Player m_player;
    vector<Bullet> m_bullet;

public:

//=======================================================
//  FUNCTIONS
private:
    void SetGame();
    void SetGameLevel(int GameLevel);
    void GetKeyState();

    void CreateBarrage(int BulletCount);        //  ź�� ����
    void ClearRainOfBullet();                   //  ź�� ����
    void DrawBarrage(HDC hdc);                  //  ź�� �׸���

    void PlayGame();
    bool Collider(RECT* rt1, RECT* rt2);

public:
    MainGame();
    ~MainGame();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;


};

