#include "stdafx.h"
#include "GameoverScene.h"
#include "SpritesObject.h"

GameoverScene::GameoverScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


GameoverScene::~GameoverScene()
{
}

void GameoverScene::Update()
{
    m_gameoverBgImg->SetAlpha(m_gameoverBgAlpha);
    m_gameoverBgAlpha += 5.0f;
    if (m_gameoverBgAlpha > 255.0f)
    {
        m_gameoverBgAlpha = 255.0f;
        if (g_pTimerManager->TickSimpleTimer("gameover") > 25)
        {
            m_gameoverImg->SetAlpha(m_gameoverAlpha);
            m_gameoverAlpha += 10.0f;
            if (m_gameoverAlpha > 255.0f)
            {
                m_gameoverAlpha = 255.0f;
            }
        }
    }

    m_gameoverBgImg->Update();
    m_gameoverImg->Update();
    m_gameoverImg->NextFrameY();
}

void GameoverScene::Render()
{
    m_gameoverBgImg->Render();
    m_gameoverImg->GetSpritesImg()->SpritesRender(g_hDC, m_gameoverImg->GetBodyRect(), 0, m_gameoverImg->GetFrameY());
}

void GameoverScene::Setup()
{
    g_pTimerManager->AddSimpleTimer("gameover");
    m_gameoverBgAlpha = 0.0f;
    m_gameoverBgImg = new SpritesObject;
    m_gameoverBgImg->SetBodyImg(g_pImgManager->FindImage("splash-bg"));
    m_gameoverBgImg->Setup(GLOBAL_CENTER_POS, GLOBAL_WIN_SIZE);
    m_gameoverBgImg->SetBodyRect(g_pDrawHelper->MakeRect(GLOBAL_CENTER_POS, GLOBAL_WIN_SIZE));
    m_gameoverBgImg->SetAlpha(m_gameoverBgAlpha);
    m_gameoverBgImg->SetupForSprites(1, 1);

    m_gameoverAlpha = 0.0f;
    m_gameoverImg = new SpritesObject;
    m_gameoverImg->SetBodyImg(g_pImgManager->FindImage("gameover"));
    m_gameoverImg->Setup(GLOBAL_CENTER_POS, m_gameoverImg->GetBodyImg()->GetSize());
    m_gameoverImg->SetBodyRect(g_pDrawHelper->MakeRect(m_gameoverImg->GetPos(), m_gameoverImg->GetSize()));
    m_gameoverImg->SetAlpha(m_gameoverAlpha);
    m_gameoverImg->SetupForSprites(1, 4);
    m_gameoverImg->SetBodySpeed({ -1.0f, 0.0f });
}

void GameoverScene::LoadImageResources()
{
    g_pImgManager->AddImage("gameover", "images/img-gameover.bmp", 440, 268);           //  439 x 268px _ 1 x 4
}

void GameoverScene::DeleteScene()
{
}