#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
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
    m_wind.Setup();
}

void MainGame::Update()
{
    GameNode::Update();
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
        m_arrow.Update();
        PlayerController();
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
    SystemController();
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
    m_stadium.Render();
    m_player.Render();
    m_target.Render();
    m_arrow.Render();
    m_wind.Render();
#ifdef _DEBUG
    char infoMsg[128];
    sprintf_s(infoMsg, "mouse x : %d  /  y : %d", g_ptMouse.x, g_ptMouse.y);
    TextOut(g_hDC, 0, 0, infoMsg, strlen(infoMsg));
    sprintf_s(infoMsg, "wind x : %f  /  y : %f  /  z : %f", m_wind.GetSpeed3D().x, m_wind.GetSpeed3D().y, m_wind.GetSpeed3D().z);
    TextOut(g_hDC, 0, 15, infoMsg, strlen(infoMsg));
    sprintf_s(infoMsg, "arrow x : %f  /  y : %f  /  z : %f", m_arrow.GetSpeed3D().x, m_arrow.GetSpeed3D().y, m_arrow.GetSpeed3D().z);
    TextOut(g_hDC, 0, 30, infoMsg, strlen(infoMsg));

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
        m_player.Shoot();
    }
    else
    {
        //  IF POWER GAUGE REMAIN
            //  SHOT ARROW 1
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
            m_currGameState = GAME_PLAYING;
            break;
        case GAME_PLAYING:
            m_currGameState = GAME_PAUSE;
            break;
        case GAME_PAUSE:
            m_currGameState = m_prevGameState;
            break;
        case GAME_CLEAR:
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