#include "stdafx.h"
#include "TileObject.h"


TileObject::TileObject()
{
}


TileObject::~TileObject()
{
}

void TileObject::Update()
{
	m_dPos.x = m_startPos.x + m_nGridPosX * m_nSize.w;
	m_dPos.y = m_startPos.y + m_nGridPosY * m_nSize.h;
	m_rtBody = { (int)m_dPos.x, (int)m_dPos.y, (int)m_dPos.x + m_nSize.w, (int)m_dPos.y + m_nSize.h };
}

void TileObject::Render(HDC hdc)
{
    m_imgBody->TransRender(hdc, m_rtBody, 255); 
#ifdef _DEBUG
	char infoMsg[128];
	sprintf_s(infoMsg, "posx : %.0f / posy : %.0f", m_dPos.x, m_dPos.y);
	TextOut(hdc, m_rtBody.left, m_rtBody.top, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}
