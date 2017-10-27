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
	m_pPlayer->SetBodySpeed({ 0.0f, 0.0f });
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
		else if (m_gameMap.GetBodyPos().x > -1400.0f)
		{
			m_gameMap.SetBodySpeedX(-5.0f);
			m_pPlayer->SetBodySpeedX(0.0f);
		}
	}

	m_gameMap.Update();
	m_pPlayer->SetStartPos(m_gameMap.GetBodyPos());
	m_pPlayer->Update();
}

void GameScene::Render()
{
	m_gameMap.Render();
	m_pPlayer->Render();
	g_pImgManager->Render("map-buffer", g_hDC);
	int left = (int)(m_pPlayer->GetBodyPos().x - m_gameMap.GetBodyPos().x);
	int top = (int)m_pPlayer->GetBodyPos().y;
	Rectangle(g_pImgManager->FindImage("minimap")->GetMemDC(), left - 30, top - 30, left + 30, top + 30);
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "");
    TextOut(g_hDC, 0, 30, infoMsg, (int)strlen(infoMsg));
#else

#endif // _DEBUG
}

void GameScene::Setup()
{
    m_gameMap.Start();

    m_pPlayer = new Player;
    m_pPlayer->SetBodyImg(g_pImgManager->FindImage("player"));
    m_pPlayer->SetBodySize({ 125, 125 });
    m_pPlayer->SetupForSprites(6, 3);
	m_pPlayer->SetMapTiles(m_gameMap.GetMapTiles());
}

void GameScene::LoadImageResources()
{
    g_pImgManager->AddImage("player", "images/player-sprites-sheet.bmp", 192, 96);  //  32 x 32px _ 6 x 3
}

void GameScene::DeleteScene()
{
}