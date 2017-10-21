#include "stdafx.h"
#include "LoadingScene.h"


LoadingScene::LoadingScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
    AddComponentsToScene();
    g_pTimerManager->AddSimpleTimer("loading");
}


LoadingScene::~LoadingScene()
{
}

void LoadingScene::Update()
{
    m_logo.SetAlpha(m_logo.GetAlpha() + 2.0f);
    if (m_logo.GetAlpha() > 255.0f)
    {
        m_logo.SetAlpha(255.0f);
        if (g_pTimerManager->TickSimpleTimer("loading") > 300)
        {
            *m_currGameState = GAME_READY;
        }
    }
    m_logo.Update();
}

void LoadingScene::Render()
{
    m_logo.Render();
}

void LoadingScene::Setup()
{
    UnitPos centerPos = g_pGeoHelper->GetCenterPointWindow();
    m_logo.Setup(centerPos, { 512, 1024 });
    m_logo.SetBodySize({ 512, 1024 });
    m_logo.SetBodyRect(g_pDrawHelper->MakeRect(m_logo.GetPos(), m_logo.GetSize()));
    m_logo.SetBodyImg(g_pImgManager->FindImage("logo-komastar"));
    m_logo.SetupForSprites(1, 1);
    m_logo.SetAlpha(0.0f);
}

void LoadingScene::LoadImageResources()
{
    //  LOGO IMAGE
    g_pImgManager->AddImage("logo-komastar", "images/logo-komastar.bmp", 512, 1024);
}

void LoadingScene::AddComponentsToScene()
{
    //g_pScnManager->AddGameObjToScn("loading", &m_logo);
}

void LoadingScene::DeleteScene()
{
    //g_pScnManager->DeleteSceneByKey("loading");
}
