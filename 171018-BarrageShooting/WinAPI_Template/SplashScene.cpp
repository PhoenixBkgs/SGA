#include "stdafx.h"
#include "SplashScene.h"


SplashScene::SplashScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


SplashScene::~SplashScene()
{
}

void SplashScene::Update()
{
    m_startBtn.Update();
}

void SplashScene::Render()
{
    m_bgImg.Render();
    m_bgDecoImg.Render();
    m_titleImg.Render();
    m_startBtn.Render();
}

void SplashScene::Setup()
{
    m_bgImg.Setup(GLOBAL_CENTER_POS, GLOBAL_WIN_SIZE);
    m_bgImg.SetBodyImg(g_pImgManager->FindImage("splash-bg"));
    m_bgImg.SetupForSprites(1, 1);

    UnitSize bgDecoSize = g_pImgManager->FindImage("splash-deco")->GetSize();
    m_bgDecoImg.SetBodyPos({ (double)(W_WIDTH - bgDecoSize.w * 0.5f), GLOBAL_CENTER_POS.y * 0.5f });
    m_bgDecoImg.SetBodySize(bgDecoSize);
    m_bgDecoImg.SetBodyRect(g_pDrawHelper->MakeRect(m_bgDecoImg.GetPos(), m_bgDecoImg.GetSize()));
    m_bgDecoImg.SetBodyImg(g_pImgManager->FindImage("splash-deco"));
    m_bgDecoImg.SetupForSprites(1, 1);

    UnitSize titleSize = g_pImgManager->FindImage("title")->GetSize();
    m_titleImg.Setup(GLOBAL_CENTER_POS, titleSize);
    m_titleImg.SetBodyImg(g_pImgManager->FindImage("title"));
    m_titleImg.SetupForSprites(1, 1);

    m_startBtn.Setup({ GLOBAL_CENTER_POS.x, GLOBAL_CENTER_POS.y + 400.0f }, { 213, 65 });
    m_startBtn.SetState(m_currGameState);
    m_startBtn.SetBodyImg(g_pImgManager->FindImage("start-button"));
    m_startBtn.SetupForSprites(1, 1);
}

void SplashScene::LoadImageResources()
{
    //  READY SCREEN
    g_pImgManager->AddImage("splash-bg", "images/img-splash-bg.bmp", 640, 1023);
    g_pImgManager->AddImage("splash-deco", "images/img-splash-deco.bmp", 366, 537);
    g_pImgManager->AddImage("title", "images/img-title.bmp", 169, 408);
    g_pImgManager->AddImage("start-button", "images/img-start-button.bmp", 213, 65);
}

void SplashScene::DeleteScene()
{
    g_pScnManager->DeleteSceneByKey("ready");
}