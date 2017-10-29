#include "stdafx.h"
#include "LoadingScene.h"


LoadingScene::LoadingScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
    g_pTimerManager->AddSimpleTimer("loading");
}


LoadingScene::~LoadingScene()
{
}

void LoadingScene::Update()
{
#ifdef _DEBUG
    m_sprTitle.SetAlpha(m_sprTitle.GetAlpha() + 20.0f);
#else
    m_sprTitle.SetAlpha(m_sprTitle.GetAlpha() + 2.0f);
#endif // _DEBUG

    if (m_sprTitle.GetAlpha() > 255.0f)
    {
        m_sprTitle.SetAlpha(255.0f);
#ifdef _DEBUG
        if (g_pTimerManager->TickSimpleTimer("loading") > 100)
#else
        if (g_pTimerManager->TickSimpleTimer("loading") > 300)
#endif // _DEBUG
        {
            *m_currGameState = GAME_PLAYING;
        }
    }
    m_sprTitle.Update();
}

void LoadingScene::Render()
{
    m_sprTitle.Render();
}

void LoadingScene::Setup()
{
    UnitPos centerPos = g_pGeoHelper->GetCenterPointWindow();
    m_sprTitle.Setup(centerPos, { 1600, 900 });
    m_sprTitle.SetBodySize({ 1600, 900 });
    m_sprTitle.SetBodyRect(g_pDrawHelper->MakeRect(m_sprTitle.GetBodyPos(), m_sprTitle.GetBodySize()));
    m_sprTitle.SetBodyImg(g_pImgManager->FindImage("logo-komastar"));
    m_sprTitle.SetupForSprites(1, 1);
    m_sprTitle.SetAlpha(0.0f);
}

void LoadingScene::LoadImageResources()
{
    //  LOGO IMAGE
    g_pImgManager->AddImage("logo-komastar", "images/logo-komastar.bmp", 1600, 900);
}

void LoadingScene::DeleteScene()
{
}
