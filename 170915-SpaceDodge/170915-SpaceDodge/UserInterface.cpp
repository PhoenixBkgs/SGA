#include "stdafx.h"
#include "UserInterface.h"


UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::SetInfoBar(int GameLevel, int RemainBullet)
{
    sprintf_s(m_stInfoBar.GameLevel, "���� ���� : %d", GameLevel);
}

void UserInterface::DrawInfoBar(HDC* hdc)
{
    //char str[128];
    //sprintf_s(str, "���� ���� : %d", m_gameLvl);
    TextOut(*hdc, 10, 10, m_stInfoBar.GameLevel, strlen(m_stInfoBar.GameLevel));
}

