#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    srand(time(NULL));
    LoadAllResources();
    Start();
}


MainGame::~MainGame()
{
}

void MainGame::Start()
{
    m_currGameState = GAME_READY;
    //  MUTUAL REF
    m_player.SetArrow(&m_arrow);
    m_arrow.SetPlayer(&m_player);
    m_arrow.SetWind(&m_wind);
    m_arrow.SetTarget(&m_target);
    m_wind.Setup();
    m_target.SetWind(&m_wind);
}

void MainGame::Update()
{
    GameNode::Update();
    SystemController();
    switch (m_currGameState)
    {
    case GAME_PAUSE:
        return;
    case GAME_READY:
    {
        Reset();
        break;
    }
    case GAME_PLAYING:
    {
        m_player.Update();
        m_arrow.Update();
        m_target.Update();
        PlayerController();
        if (m_arrow.GetArrowRemain() < 1)
        {
            //  GAME END
            m_currGameState = GAME_OVER;
        }
        break;
    }
    case GAME_CLEAR:
    {
        m_wind.Setup();
        break;
    }
    case GAME_OVER:
        break;
    }
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
    if (m_currGameState == GAME_OVER)
    {
        //  GAME OVER SCREEN
        g_pDrawHelper->m_textBoxInfo.FontName = "Consolas";
        g_pDrawHelper->m_textBoxInfo.FontColor = _RGBA{ 0, 0, 0, 0 };
        g_pDrawHelper->m_textBoxInfo.IsVisibleBox = false;
        RECT rt = { 0, 200, W_WIDTH, 400 };
        char infoMsg[128];
        sprintf_s(infoMsg, "SCORE : %d", m_player.GetScore());
        g_pDrawHelper->DrawTextBox(g_hDC, rt, infoMsg);
        return;
    }
    m_stadium.Render();
    m_player.Render();
    m_target.Render();
    m_arrow.Render();
    m_wind.Render();
    m_target.AimRender();
    m_player.GaugeRender();
    m_arrow.DestPointRender();
#ifdef _DEBUG
    char infoMsg[128];
    int x = g_ptMouse.x - W_WIDTH * 0.5f;
    int y = g_ptMouse.y - W_HEIGHT * 0.5f;
    sprintf_s(infoMsg, "AIM x : %d  /  y : %d", x, y);
    TextOut(g_hDC, 0, 0, infoMsg, strlen(infoMsg));
    sprintf_s(infoMsg, "wind x : %f  /  y : %f  /  z : %f", m_wind.GetSpeed3D().x, m_wind.GetSpeed3D().y, m_wind.GetSpeed3D().z);
    TextOut(g_hDC, 0, 15, infoMsg, strlen(infoMsg));
    sprintf_s(infoMsg, "arrow x : %f  /  y : %f  /  z : %f", m_arrow.GetSpeed3D().x, m_arrow.GetSpeed3D().y, m_arrow.GetSpeed3D().z);
    TextOut(g_hDC, 0, 30, infoMsg, strlen(infoMsg));
    sprintf_s(infoMsg, "power : %f", m_player.GetPowerGauge());
    TextOut(g_hDC, 0, 45, infoMsg, strlen(infoMsg));
    sprintf_s(infoMsg, "score : %d  /  remain : %d", m_player.GetScore(), m_arrow.GetArrowRemain());
    TextOut(g_hDC, 0, 60, infoMsg, strlen(infoMsg));
#endif // _DEBUG

}

void MainGame::Reset()
{
    m_stadium.Setup();
    m_player.Setup();
    m_target.Setup();
    m_arrow.Setup();
}

#pragma region LOAD_RESOURCES
void MainGame::LoadAllResources()
{
    LoadImageResources();
    LoadSoundResources();
}

void MainGame::LoadImageResources()
{
}

void MainGame::LoadSoundResources()
{
}
#pragma endregion

#pragma region CONTROLLER
void MainGame::PlayerController()
{
    //  MOUSE L BUTTON
    if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
    {
        //  POWER GAUGE UP
        m_player.PullTrigger();
    }
    else
    {
        if (m_player.GetIsPulling() == true)
        {
            m_player.Shoot();
            m_player.SetPowerGauge(0.0f);
        }
    }
}

void MainGame::SystemController()
{
    if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
    {
        E_GAME_STATE tempState = m_currGameState;
        switch (m_currGameState)
        {
        case GAME_READY:
            m_prevGameState = GAME_READY;
            m_currGameState = GAME_PLAYING;
            break;
        case GAME_PLAYING:
            m_prevGameState = GAME_PLAYING;
            m_currGameState = GAME_CLEAR;
            break;
        case GAME_PAUSE:
            m_currGameState = m_prevGameState;
            break;
        case GAME_CLEAR:
            m_currGameState = GAME_READY;
            break;
        case GAME_OVER:
            break;
        default:
            break;
        }
        m_prevGameState = tempState;
    }
}
#pragma endregion