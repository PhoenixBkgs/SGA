#include "stdafx.h"
#include "Button.h"

#pragma region START_BUTTON
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
    m_nSize = Size;
    m_dPos = Pos;
    m_originSize = Size;
    m_bIsSetup = true;

    g_pTimerManager->AddOnOffTimer("start-btn");
}

void StartButton::Update()
{
    float magnifier = g_pTimerManager->FindOnOffTick("start-btn") * 0.1f;
    g_pTimerManager->TickOnOffTimer("start-btn");

    magnifier += 1.0f;
    m_nSize = { (int)(m_originSize.w * magnifier), (int)(m_originSize.h * magnifier) };

    if (PtInRect(&m_rtBody, g_ptMouse))
    {
        m_nSize = { (int)(m_originSize.w * 1.3f), (int)(m_originSize.h * 1.3f) };
        if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
        {
            *m_currGameState = GAME_PLAYING;
        }
    }

    SpritesObject::Update();
}

void StartButton::Render()
{
    SpritesObject::Render();
}
#pragma endregion

#pragma region SELECT_BUTTON
SelectButton::SelectButton()
{
}

SelectButton::~SelectButton()
{
}

void SelectButton::Update()
{
}

void SelectButton::Render()
{
}
#pragma endregion