#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


GameScene::~GameScene()
{
    SAFE_DELETE(m_pPlayer);
}

void GameScene::Update()
{
    if (m_pPad->GetBodyPos().x > 600.0f)
    {
        UnitSpeed speed = m_pPad->GetBodySpeed();
        speed.x = -speed.x;
        m_pPad->SetBodySpeed(speed);
    }
    if (m_pPad->GetBodyPos().x < 200.0f)
    {
        UnitSpeed speed = m_pPad->GetBodySpeed();
        speed.x = -speed.x;
        m_pPad->SetBodySpeed(speed);
    }
    m_pPlayer->Update();
    m_pPad->Update();
}

void GameScene::Render()
{
    g_pImgManager->FindImage("sky")->FastRender(g_hDC);
    g_pImgManager->FindImage("land")->SpritesRender(g_hDC, { 0, 0, W_WIDTH, W_HEIGHT }, 0, 0, 255);
    m_pPlayer->Render();
    m_pPad->Render();
#ifdef _DEBUG
    /*
    char infoMsg[128];
    sprintf_s(infoMsg, "");
    TextOut(g_hDC, 0, 30, infoMsg, (int)strlen(infoMsg));
    */
#endif // _DEBUG
}

void GameScene::Setup()
{
    m_pPlayer = new Player;
    m_pPlayer->SetBodyImg(g_pImgManager->FindImage("player"));
    m_pPlayer->SetBodySize({ 64, 64 });
    m_pPlayer->SetBodyPos({ 150.0f, 150.0f });
    m_pPlayer->SetupForSprites(6, 3);

    m_pPad = new SpritesObject;
    m_pPad->SetBodyImg(g_pImgManager->FindImage("pad"));
    m_pPad->SetupForSprites(8, 3);
    m_pPad->SetBodySize({ 128, 64 });
    m_pPad->SetBodyPos({ 300.0f, 200.0f });
    m_pPad->SetBodySpeed({ 2.0f, 0.0f });
    m_pPad->SetBodyRect(g_pDrawHelper->MakeRect(m_pPad->GetBodyPos(), m_pPad->GetBodySize()));
    m_pPad->SetFrameX(0);
    m_pPad->SetFrameY(0);
    m_pPlayer->SetPad(m_pPad);
}

void GameScene::LoadImageResources()
{
    g_pImgManager->AddImage("player", "images/player-sprites-sheet.bmp", 192, 96);  //  32 x 32px _ 6 x 3
    g_pImgManager->AddImage("land", "images/temp-land.bmp", 1600, 900);
    g_pImgManager->AddImage("sky", "images/sky.bmp", 1600, 900);
    g_pImgManager->FindImage("land")->SetSpritesSize({ 1600, 900 });

    g_pImgManager->AddImage("pad", "images/tile-sprites-sheet.bmp", 256, 96);
}

void GameScene::DeleteScene()
{
}