#include "stdafx.h"
#include "MenuScene.h"

MenuScene::MenuScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
    AddComponentsToScene();
}


MenuScene::~MenuScene()
{
}

void MenuScene::LoadImageResources()
{
    //  MENU
    g_pImgManager->AddImage("menu", "images/img-menu.bmp", 144, 255);
}

void MenuScene::Setup()
{
    UnitPos centerPos = g_pGeoHelper->GetCenterPointWindow();
    m_pauseBgImg.Setup(centerPos, { W_WIDTH, W_HEIGHT });
    m_pauseBgImg.SetBodyImg(g_pImgManager->FindImage("splash-bg"));
    m_pauseBgImg.SetupForSprites(1, 1);
    m_pauseBgImg.SetAlpha(128.0f);

    m_menuImg.SetBodyImg(g_pImgManager->FindImage("menu"));
    m_menuImg.Setup(centerPos, m_menuImg.GetBodyImg()->GetSize());
    m_menuImg.SetupForSprites(1, 1);
}

void MenuScene::AddComponentsToScene()
{
    g_pScnManager->AddGameObjToScn("pause", &m_pauseBgImg);
    g_pScnManager->AddGameObjToScn("pause", &m_menuImg);
}

void MenuScene::DeleteScene()
{
    g_pScnManager->DeleteSceneByKey("pause");
}