#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(E_GAME_STATE* State)
{
    m_nGameTimer = 0;
    SyncGameState(State);
    LoadImageResources();
}


GameScene::~GameScene()
{
    SAFE_DELETE(m_pPlayer);
}

void GameScene::Update()
{
    if (m_pPlayer->IsAlive() == false)
    {
        *m_currGameState = GAME_OVER;
    }

    if (m_pPlayer->IsClear())
    {
        *m_currGameState = GAME_CLEAR;
    }

    if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        m_pPlayer->SetBodySpeedX(-5.0f);
        if (m_pPlayer->GetBodyPos().x > W_WIDTH * 0.4f)
        {
        }
        else if (m_gameMap.GetBodyPos().x < 0.0f)
        {
            m_gameMap.SetBodySpeedX(5.0f);
            m_pPlayer->SetBodySpeedX(0.0f);
        }
    }
    else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        m_pPlayer->SetBodySpeedX(5.0f);
        if (m_pPlayer->GetBodyPos().x < W_WIDTH * 0.6f)
        {
        }
        else if (m_gameMap.GetBodyPos().x > -(m_nMapSize.w - W_WIDTH))
        {
            m_gameMap.SetBodySpeedX(-5.0f);
            m_pPlayer->SetBodySpeedX(0.0f);
        }
    }

    for (auto iter = m_vecGameObjs.begin(); iter != m_vecGameObjs.end(); iter++)
    {
        iter->SetBodySpeedX(m_gameMap.GetBodySpeedX());
        iter->Update();
    }

    m_nGameTimer++;

	m_gameMap.Update();

	m_pPlayer->SetStartPos(m_gameMap.GetBodyPos());
	m_pPlayer->Update();
    for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); iter++)
    {
        RECT rt;
        if (IntersectRect(&rt, &m_pPlayer->GetHBoxRect(), &iter->GetHBoxRect()))
        {
            if (m_pPlayer->GetBodyPos().y < iter->GetBodyPos().y)
            {
                iter->SetDead();
            }
            else
            {
                m_pPlayer->SetDead();
            }
        }

        iter->SumBodySpeedX(m_gameMap.GetBodySpeedX());
        iter->Update();
    }
    m_pPlayer->SetBodySpeed({ 0.0f, 0.0f });

    for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end();)
    {
        if (iter->IsAlive() == false)
        {
            iter = m_vecEnemy.erase(iter);
        }
        else
        {
            iter++;
        }
    }
    
    for (auto iter = m_vecGameObjs.begin(); iter != m_vecGameObjs.end();)
    {
        if (iter->IsAlive() == false)
        {
            iter = m_vecGameObjs.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

void GameScene::Render()
{
    g_pImgManager->Render("background", g_hDC, { m_gameMap.GetBodyPos().x, 0.0f });
	m_gameMap.Render();
	m_pPlayer->Render();
    for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); iter++)
    {
        iter->Render();
    }
	g_pImgManager->Render("map-buffer", g_hDC);
	int left = (int)(m_pPlayer->GetBodyPos().x - m_gameMap.GetBodyPos().x);
	int top = (int)m_pPlayer->GetBodyPos().y;

    left /= 10;
    top /= 10;
	Rectangle(g_pImgManager->FindImage("minimap")->GetMemDC(), left - 2, top - 2, left + 2, top + 2);
    for (auto iter = m_vecGameObjs.begin(); iter != m_vecGameObjs.end(); iter++)
    {
#ifdef _DEBUG
        char infoMsg[128];
        sprintf_s(infoMsg, "%.0f, %.0f", iter->GetBodyPos().x, iter->GetBodyPos().y);
        TextOut(g_hDC, iter->GetBodyPos().x, iter->GetBodyPos().y, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
        iter->Render();
    }

    RECT rt = { 0, 0, 200, 50 };
    string szScore = to_string(m_nGameTimer);
    g_pDrawHelper->m_textBoxInfo.FontColor = { 0, 0, 0, 255 };
    g_pDrawHelper->DrawTextBox(g_hDC, rt, szScore);

    char infoMsg[128];
    sprintf_s(infoMsg, "%.0f", m_pPlayer->GetBoosterGauge());
    TextOut(g_hDC, 0, 400, infoMsg, (int)strlen(infoMsg));
}

void GameScene::Setup()
{
    m_gameMap.SetMapSize(m_nMapSize);
    m_gameMap.Start();

    m_pPlayer = new Player;
    m_pPlayer->SetGameObjs(&m_vecGameObjs);
    m_pPlayer->SetBodyImg(g_pImgManager->FindImage("player"));
    m_pPlayer->SetBodySize({ 50, 50 });
    m_pPlayer->SetBodyPos({ 200.0f, 200.0f });
    m_pPlayer->SetupForSprites(10, 5);
	m_pPlayer->SetMapTiles(m_gameMap.GetMapTiles());

    Enemy genEnemy;
    genEnemy.SetTagName("1");
    genEnemy.SetMapPos(m_gameMap.GetMapPosRef());
    genEnemy.SetBodyImg(g_pImgManager->FindImage("enemy"));
    genEnemy.SetBodyPos({ 375.0f, 450.0f });
    genEnemy.SetBodySize({ 75, 75 });
    genEnemy.SetStartPos({ 375.0f, 450.0f });
    genEnemy.SetupForSprites(6, 6);
    m_vecEnemy.push_back(genEnemy);
}

void GameScene::LoadImageResources()
{
    g_pImgManager->AddImage("player", "images/sprites-player.bmp", 160, 80);  //  32 x 32px
    g_pImgManager->AddImage("background", "images/bg.bmp", 3000, 900);
    g_pImgManager->AddImage("enemy", "images/enemy-sprites-sheet.bmp", 192, 192);
}

void GameScene::DeleteScene()
{
}