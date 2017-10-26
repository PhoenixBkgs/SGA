#include "stdafx.h"
#include "MapObject.h"


MapObject::MapObject()
{
    GameObject::GameObject();
}

MapObject::~MapObject()
{
}

void MapObject::Start()
{
	m_brush = CreateSolidBrush(RGB(255, 0, 255));
    //  read map data
    ifstream i;
    i.open("data/map.txt", ios_base::in);
	string szTemp;
	while (i >> szTemp)
	{
		m_gameMapData.append(szTemp);
	}
    i.close();

    //  set body size
    m_nSize.w = 3000;
    m_nSize.h = 900;

	m_dPos = { 0.0f, 0.0f };
    m_startPos = { 75.0f, 75.0f };

	m_imgTile = g_pImgManager->AddImage("tile", "images/tile.bmp", 32, 32);
	m_pSkyImg = g_pImgManager->AddImage("sky", "images/sky.bmp", 1600, 900);
	g_pImgManager->AddImage("map-buffer", m_nSize.w, m_nSize.h);
	m_pMapbuffer = g_pImgManager->FindImage("map-buffer");
	m_pFogImg = g_pImgManager->AddImage("fog", 3000, 900);
	PatBlt(g_pImgManager->FindImage("fog")->GetMemDC(), 0, 0, 3000, 900, BLACKNESS);
	m_pMinimap = g_pImgManager->FindImage("minimap");

	int idx = 0;

    for (int row = 0; row < TILE_ROW_COUNT; row++)
    {
		for (int col = 0; col < TILE_COL_COUNT; col++)
		{
			char temp = m_gameMapData.at(idx);
			int tempInt = atoi(&temp);
			if (tempInt == 0)
			{
			}
			else
			{
				TileObject tile;
				tile.SetStartPos(m_startPos);
				tile.SetBodySize({ 150, 150 });
				tile.SetBodyPos({ (double)(col * tile.GetBodySize().w) + m_startPos.x, (double)(row * tile.GetBodySize().h) + m_startPos.y });
				tile.SetBodyImg(m_imgTile);
				tile.SetGridPosX(col);
				tile.SetGridPosY(row);
				double x = tile.GetBodyPos().x;
				double y = tile.GetBodyPos().y;
				m_vecTiles.push_back(tile);
			}
			idx++;
		}
    }
}

void MapObject::Update()
{
	GameObject::Update();

	for (auto tileUpdateIter = m_vecTiles.begin(); tileUpdateIter != m_vecTiles.end(); tileUpdateIter++)
	{
		tileUpdateIter->SetStartPos(m_dPos);
		tileUpdateIter->Update();
	}
	m_dSpeed = { 0.0f, 0.0f };
}

void MapObject::Render()
{
    m_pSkyImg->Render(g_hDC, 0, 0, W_WIDTH, W_HEIGHT); 
	m_pSkyImg->Render(m_pMinimap->GetMemDC(), 0, 0, 3000, 900);
	RECT rt = { 0, 0, W_WIDTH, W_HEIGHT };
	FillRect(m_pMapbuffer->GetMemDC(), &rt, m_brush);
	for (auto tileRenderIter = m_vecTiles.begin(); tileRenderIter != m_vecTiles.end(); tileRenderIter++)
	{
		tileRenderIter->Render(m_pMapbuffer->GetMemDC());
		tileRenderIter->SetStartPos({ 0.0f, 0.0f });
		tileRenderIter->Update();
		tileRenderIter->Render(m_pMinimap->GetMemDC());
	}
	m_pFogImg->Render(m_pMinimap->GetMemDC(), 0, 0, -(int)m_dPos.x, 900, 0, 0, 3000, 900, 128);
	m_pFogImg->Render(m_pMinimap->GetMemDC(), -(int)m_dPos.x + W_WIDTH, 0, W_WIDTH, 900, 0, 0, 3000, 900, 128);

#ifdef _DEBUG
	char infoMsg[128];
	sprintf_s(infoMsg, "posx : %f / posy : %f", m_dPos.x, m_dPos.y);
	TextOut(g_hDC, 750, 450, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}
