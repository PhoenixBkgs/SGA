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

	m_dPos = { 0.0f, 0.0f };
    m_startPos = { 75.0f, 75.0f };

    m_pWorldmap = g_pImgManager->AddImage("map", "images/map.bmp", m_nMapSize.w, m_nMapSize.h);
	g_pImgManager->AddImage("map-buffer", m_nMapSize.w, m_nMapSize.h);
	m_pMapbuffer = g_pImgManager->FindImage("map-buffer");
	m_pFogImg = g_pImgManager->AddImage("fog", m_nMapSize.w * 0.1f, m_nMapSize.h * 0.1f);
	PatBlt(g_pImgManager->FindImage("fog")->GetMemDC(), 0, 0, m_nMapSize.w * 0.1f, m_nMapSize.h * 0.1f, BLACKNESS);
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
    m_pWorldmap->Render(m_pMinimap->GetMemDC(), 0, 0, m_nMapSize.w * 0.1f, m_nMapSize.h * 0.1f);
	m_pFogImg->Render(m_pMinimap->GetMemDC(), 0, 0
                                            , -(int)m_dPos.x * 0.1f, m_nMapSize.h * 0.1f, 0
                                            , 0, m_nMapSize.w * 0.1f, m_nMapSize.h * 0.1f
                                            , 128);
	m_pFogImg->Render(m_pMinimap->GetMemDC(), (-(int)m_dPos.x + W_WIDTH) * 0.1f, 0
                                            , (m_nMapSize.w) * 0.1f, m_nMapSize.h * 0.1f
                                            , 0, 0
                                            , m_pFogImg->GetWidth(), m_pFogImg->GetHeight()
                                            , 128);

    //  worldmap
    RECT rt = { 0, 0, m_pWorldmap->GetWidth(), m_pWorldmap->GetHeight() };
    FillRect(m_pMapbuffer->GetMemDC(), &rt, m_brush);
    m_pWorldmap->Render(m_pMapbuffer->GetMemDC(), m_dPos.x, m_dPos.y);
    //m_pWorldmap->Render(m_pMapbuffer->GetMemDC(), 0, 0);
}