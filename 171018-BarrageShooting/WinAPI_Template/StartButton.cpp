#include "stdafx.h"
#include "StartButton.h"


StartButton::StartButton()
    : m_bIsSetup(true)
    , m_currGameState(NULL)
{
}


StartButton::~StartButton()
{
}

void StartButton::Setup(UnitPos Pos, UnitSize Size)
{
    m_rtBody = g_pDrawHelper->MakeRect(Pos, Size);
    m_bIsSetup = true;
}

void StartButton::Update()
{
    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        if (PtInRect(&m_rtBody, g_ptMouse))
        {
            *m_currGameState = GAME_PLAYING;
        }
    }
}

void StartButton::Render()
{
    SpritesObject::Render();
}
