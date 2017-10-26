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
    g_pImgManager->AddImage("sky", "sky.bmp", 1600, 900);

	g_pImgManager->AddImage("map-buffer", m_nSize.w, m_nSize.h);

	int idx = 0;

    for (int row = 0; row < TILE_ROW_COUNT; row++)
    {
		for (int col = 0; col < TILE_COL_COUNT; col++)
		{
			char temp = m_gameMapData.at(idx);
			int tempInt = atoi(&temp);
			cout << "tempInt : " << tempInt << " / ";
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
				double x = tile.GetBodyPos().x;
				double y = tile.GetBodyPos().y;
				cout << idx << " / " << " " << x << ", " << y;
				m_vecTiles.push_back(tile);
			}
			cout << endl;
			idx++;
		}
    }
}

void MapObject::Update()
{
	GameObject::Update();
	cout << m_dPos.x << ", " << m_dPos.y << endl;
	for (auto tileUpdateIter = m_vecTiles.begin(); tileUpdateIter != m_vecTiles.end(); tileUpdateIter++)
	{
		tileUpdateIter->SetBodySpeed(m_dSpeed);
		tileUpdateIter->Update();
	}
	m_dSpeed = { 0.0f, 0.0f };
}

void MapObject::Render()
{
    g_pImgManager->FindImage("sky")->Render(g_hDC, { 0.0f, 0.0f }); 
	RECT rt = { 0, 0, W_WIDTH, W_HEIGHT };
	FillRect(g_pImgManager->FindImage("map-buffer")->GetMemDC(), &rt, m_brush);
	for (auto tileRenderIter = m_vecTiles.begin(); tileRenderIter != m_vecTiles.end(); tileRenderIter++)
	{
		tileRenderIter->Render(g_pImgManager->FindImage("map-buffer")->GetMemDC());
	}
	g_pImgManager->Render("map-buffer", g_hDC);
}
