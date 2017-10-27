#include "stdafx.h"
#include "MapObject.h"


MapObject::MapObject()
{
    GameObject::GameObject();
    Start();
}

MapObject::~MapObject()
{
}

void MapObject::Start()
{
	m_brush = CreateSolidBrush(RGB(255, 0, 255));

	m_dPos = { 0.0f, 0.0f };
    m_startPos = { 75.0f, 75.0f };

    m_pWorldmap = g_pImgManager->AddImage("map", "images/map.bmp", 3000, 900);
	m_pSkyImg = g_pImgManager->AddImage("sky", "images/sky.bmp", 1600, 900);
	g_pImgManager->AddImage("map-buffer", 3000, 900);
	m_pMapbuffer = g_pImgManager->FindImage("map-buffer");
	m_pFogImg = g_pImgManager->AddImage("fog", 300, 90);
	PatBlt(g_pImgManager->FindImage("fog")->GetMemDC(), 0, 0, 300, 90, BLACKNESS);
	m_pMinimap = g_pImgManager->FindImage("minimap");
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
    //  minimap
	m_pSkyImg->Render(m_pMinimap->GetMemDC(), 0, 0, 300, 90);
	m_pFogImg->Render(m_pMinimap->GetMemDC(), 0, 0, -(int)m_dPos.x, 300, 0, 0, 300, 90, 128);
	m_pFogImg->Render(m_pMinimap->GetMemDC(), -(int)m_dPos.x + W_WIDTH, 0, W_WIDTH, 300, 0, 0, 300, 90, 128);

    //  worldmap
    m_pSkyImg->Render(g_hDC, 0, 0, W_WIDTH, W_HEIGHT); 
	RECT rt = { 0, 0, W_WIDTH, W_HEIGHT };
	FillRect(m_pMapbuffer->GetMemDC(), &rt, m_brush);
    m_pWorldmap->Render(m_pMapbuffer->GetMemDC(), m_dPos.x, m_dPos.y);
#ifdef _DEBUG
	char infoMsg[128];
	sprintf_s(infoMsg, "posx : %f / posy : %f", m_dPos.x, m_dPos.y);
	TextOut(g_hDC, 750, 450, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}