#include "stdafx.h"
#include "ClearScene.h"
#include "SpritesObject.h"

ClearScene::ClearScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
}


ClearScene::~ClearScene()
{
}

void ClearScene::Update()
{
    m_clearBgImg->SetAlpha(m_clearBgAlpha);
    m_clearBgAlpha += 5.0f;
    if (m_clearBgAlpha > 255.0f)
    {
        m_clearBgAlpha = 255.0f;
        if (g_pTimerManager->TickSimpleTimer("clear") > 25)
        {
            m_continueImg->SetAlpha(m_continueAlpha);
            m_continueAlpha += 10.0f;
            if (m_continueAlpha > 255.0f)
            {
                m_continueAlpha = 255.0f;
            }
        }
    }

    if (m_continueImg->GetBodyRect().right <= 0.0f)
    {
        RECT rt = m_continueImg->GetBodyRect();
        rt.left = 0;
        rt.right = 480;
        m_continueImg->SetBodyRect(rt);
    }
    m_clearBgImg->Update();
    m_continueImg->Update();
}

void ClearScene::Render()
{
    m_clearBgImg->Render();

    UnitPos pos = m_continueImg->GetPos();
    m_continueImg->Render();
    RECT rt = m_continueImg->GetBodyRect();
    rt.left = rt.left - 480;
    rt.right = rt.right - 480;
    m_continueImg->GetSpritesImg()->SpritesRender(g_hDC, rt, 0, 0, m_continueAlpha);
    rt = m_continueImg->GetBodyRect();
    rt.left = rt.left + 480;
    rt.right = rt.right + 480;
    m_continueImg->GetSpritesImg()->SpritesRender(g_hDC, rt, 0, 0, m_continueAlpha);
    rt.left = rt.left + 480;
    rt.right = rt.right + 480;
    m_continueImg->GetSpritesImg()->SpritesRender(g_hDC, rt, 0, 0, m_continueAlpha);
}

void ClearScene::Setup()
{
    g_pTimerManager->AddSimpleTimer("clear");
    m_clearBgAlpha = 0.0f;
    m_clearBgImg = new SpritesObject;
    m_clearBgImg->SetBodyImg(g_pImgManager->FindImage("splash-bg"));
    m_clearBgImg->Setup(GLOBAL_CENTER_POS, GLOBAL_WIN_SIZE);
    m_clearBgImg->SetBodyRect(g_pDrawHelper->MakeRect(m_clearBgImg->GetPos(), m_clearBgImg->GetSize()));
    m_clearBgImg->SetAlpha(m_clearBgAlpha);
    m_clearBgImg->SetupForSprites(1, 1);

    m_continueAlpha = 0.0f;
    m_continueImg = new SpritesObject;
    m_continueImg->SetBodyImg(g_pImgManager->FindImage("continue"));
    m_continueImg->Setup(GLOBAL_CENTER_POS, m_continueImg->GetBodyImg()->GetSize());
    m_continueImg->SetBodyRect(g_pDrawHelper->MakeRect(m_continueImg->GetPos(), m_continueImg->GetSize()));
    m_continueImg->SetAlpha(m_continueAlpha);
    m_continueImg->SetupForSprites(1, 1);
    m_continueImg->SetBodySpeed({ -1.0f, 0.0f });
}

void ClearScene::LoadImageResources()
{
    g_pImgManager->AddImage("continue", "images/sprites-continue.bmp", 480, 220);
}

void ClearScene::DeleteScene()
{
}
