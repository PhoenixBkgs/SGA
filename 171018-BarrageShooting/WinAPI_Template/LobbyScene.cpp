#include "stdafx.h"
#include "LobbyScene.h"
#include "SpritesObject.h"

LobbyScene::LobbyScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


LobbyScene::~LobbyScene()
{
}

void LobbyScene::Update()
{
    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        if (PtInRect(&m_pPlayerTypeA->GetBodyRect(), g_ptMouse))
        {
            m_szSelectPlayer = "player";
            *m_currGameState = GAME_PLAYING;
        }

        if (PtInRect(&m_pPlayerTypeC->GetBodyRect(), g_ptMouse))
        {
            m_szSelectPlayer = "player2";
            *m_currGameState = GAME_PLAYING;
        }
    }
}

void LobbyScene::Render()
{
    m_bgImg->Render();
    m_pPlayerTypeA->Render();
    m_pPlayerTypeC->Render();
}

void LobbyScene::Setup()
{
    m_bgImg = new SpritesObject;
    m_bgImg->SetBodyImg(g_pImgManager->FindImage("splash-bg"));
    m_bgImg->Setup(GLOBAL_CENTER_POS, GLOBAL_WIN_SIZE);
    m_bgImg->SetBodyRect(g_pDrawHelper->MakeRect(m_bgImg->GetPos(), m_bgImg->GetSize()));
    m_bgImg->SetupForSprites(1, 1);

    m_pPlayerTypeA = new SpritesObject;
    m_pPlayerTypeA->SetBodyImg(g_pImgManager->FindImage("player-type-a"));
    m_pPlayerTypeA->Setup({ W_WIDTH * 0.5f, W_HEIGHT * 0.3f }, m_pPlayerTypeA->GetBodyImg()->GetSize());
    m_pPlayerTypeA->SetBodyRect(g_pDrawHelper->MakeRect(m_pPlayerTypeA->GetPos(), m_pPlayerTypeA->GetSize()));
    m_pPlayerTypeA->SetupForSprites(1, 1);

    m_pPlayerTypeC = new SpritesObject;
    m_pPlayerTypeC->SetBodyImg(g_pImgManager->FindImage("player-type-c"));
    m_pPlayerTypeC->Setup({ W_WIDTH * 0.5f, W_HEIGHT * 0.7f }, m_pPlayerTypeC->GetBodyImg()->GetSize());
    m_pPlayerTypeC->SetBodyRect(g_pDrawHelper->MakeRect(m_pPlayerTypeC->GetPos(), m_pPlayerTypeC->GetSize()));
    m_pPlayerTypeC->SetupForSprites(1, 1);

}

void LobbyScene::LoadImageResources()
{
    g_pImgManager->AddImage("player-type-a", "images/img-type-a.bmp", 592, 208);
    g_pImgManager->AddImage("player-type-c", "images/img-type-c.bmp", 592, 208);
}

void LobbyScene::DeleteScene()
{
}
