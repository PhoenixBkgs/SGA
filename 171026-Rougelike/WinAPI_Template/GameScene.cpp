#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(E_GAME_STATE* State)
{
    SyncGameState(State);
    LoadImageResources();
    Setup();
	m_gameMap.Start();
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
		if (m_pPlayer->GetBodyPos().x > 175)
		{
			cout << "player go left" << endl;
			m_pPlayer->SetBodySpeedX(-5.0f);
			if (m_pPlayer->GetBodyPos().x > W_WIDTH * 0.4f)
			{

			}
			else if (m_gameMap.GetBodyPos().x < 0.0f)
			{
				cout << "map go right" << endl;
				m_gameMap.SetBodySpeedX(5.0f);
				m_pPlayer->SetBodySpeedX(0.0f);
			}
		}
	}
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
	{
		if (m_pPlayer->GetBodyPos().x < W_WIDTH - 175)
		{
			cout << "player go right" << endl;
			m_pPlayer->SetBodySpeedX(5.0f);
			if (m_pPlayer->GetBodyPos().x < W_WIDTH * 0.6f)
			{

			}
			else if (m_gameMap.GetBodyPos().x > -1400.0f)
			{
				cout << "map go left" << endl;
				m_gameMap.SetBodySpeedX(-5.0f);
				m_pPlayer->SetBodySpeedX(0.0f);
			}
		}
	}

	m_gameMap.Update();
	m_pPlayer->Update();
}

void GameScene::Render()
{
	m_gameMap.Render();
	m_pPlayer->Render();
	
#ifdef _DEBUG
    /*
    char infoMsg[128];
    sprintf_s(infoMsg, "");
    TextOut(g_hDC, 0, 30, infoMsg, (int)strlen(infoMsg));
    */
#endif // _DEBUG
}

void GameScene::Setup()
{
    m_gameMap.Start();

    m_pPlayer = new Player;
    m_pPlayer->SetBodyImg(g_pImgManager->FindImage("player"));
    m_pPlayer->SetBodySize({ 64, 64 });
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