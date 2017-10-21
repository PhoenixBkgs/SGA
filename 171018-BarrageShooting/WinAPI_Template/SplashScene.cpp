#include "stdafx.h"
#include "SplashScene.h"


SplashScene::SplashScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
    AddComponentsToScene();
}


SplashScene::~SplashScene()
{
}

void SplashScene::Setup()
{
    UnitPos centerPos = g_pGeoHelper->GetCenterPointWindow();

    m_bgImg.Setup(centerPos, { W_WIDTH, W_HEIGHT });
    m_bgImg.SetBodyImg(g_pImgManager->FindImage("splash-bg"));
    m_bgImg.SetupForSprites(1, 1);

    UnitSize bgDecoSize = g_pImgManager->FindImage("splash-deco")->GetSize();
    m_bgDecoImg.SetBodyPos({ (double)(W_WIDTH - bgDecoSize.w * 0.5f), centerPos.y * 0.5f });
    m_bgDecoImg.SetBodySize(bgDecoSize);
    m_bgDecoImg.SetBodyRect(g_pDrawHelper->MakeRect(m_bgDecoImg.GetPos(), m_bgDecoImg.GetSize()));
    m_bgDecoImg.SetBodyImg(g_pImgManager->FindImage("splash-deco"));
    m_bgDecoImg.SetupForSprites(1, 1);

    UnitSize titleSize = g_pImgManager->FindImage("title")->GetSize();
    m_titleImg.Setup(centerPos, titleSize);
    m_titleImg.SetBodyImg(g_pImgManager->FindImage("title"));
    m_titleImg.SetupForSprites(1, 1);

    m_startBtn.Setup({ centerPos.x, centerPos.y + 400.0f }, { 213, 65 });
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

void SplashScene::AddComponentsToScene()
{
    g_pScnManager->AddGameObjToScn("ready", &m_bgImg);
    g_pScnManager->AddGameObjToScn("ready", &m_bgDecoImg);
    g_pScnManager->AddGameObjToScn("ready", &m_titleImg);
    g_pScnManager->AddGameObjToScn("ready", &m_startBtn);
}

void SplashScene::DeleteScene()
{
    g_pScnManager->DeleteSceneByKey("ready");
}