#include "stdafx.h"
#include "UserInterface.h"


UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::Render(HDC hdc)
{
    char msgGameover[100];
    sprintf_s(msgGameover, "GAME OVER !!!");
    PrintMessageCenter(&hdc, msgGameover);
}

void UserInterface::SetInfoBar(int GameLevel, int RemainBullet)
{
    sprintf_s(m_stInfoBar.GameLevel, "게임 레벨 : %d", GameLevel);
}

void UserInterface::DrawInfoBar(HDC* hdc)
{
    TextOut(*hdc, 10, 10, m_stInfoBar.GameLevel, strlen(m_stInfoBar.GameLevel));
}

void UserInterface::PrintMessageCenter(HDC* hdc, char * Message)
{
    int msgLength = strlen(Message);
    int msgBoxPosX = (WIN_WIDTH * 0.5) - (msgLength * 5);
    int msgBoxPosY = (WIN_HEIGHT * 0.5) - 100;

    TextOut(*hdc, msgBoxPosX, msgBoxPosY, Message, msgLength);
}

