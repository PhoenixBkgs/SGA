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
    bool m_isPlaying;
    int m_gameLvl;
    int m_gameScore;

    E_GAMESTATE m_eGameState;

    UserInterface m_ui;
    Player m_player;
    vector<Bullet> m_bullet;

public:

//=======================================================
//  FUNCTIONS
private:
    void SetGameLevel(int GameLevel);
    void GetKeyState();

    void CreateBarrage(int BulletCount);        //  Åº¸· »ý¼º
    void ClearRainOfBullet();                   //  Åº¸· Á¦°Å
    void DrawBarrage(HDC hdc);                  //  Åº¸· ±×¸®±â

    void PlayGame();

public:
    MainGame();
    ~MainGame();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;


};

