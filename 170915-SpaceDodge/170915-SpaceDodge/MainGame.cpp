#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
{
    m_isPlaying = false;
    m_gameLvl = 1;
}


MainGame::~MainGame()
{
}

void MainGame::Update()
{
    GameNode::Update();
    
    if (m_isPlaying)
    {
        m_player.Update();
        /*
        m_bullet.Update();

        RECT rt;
        for (auto iter = (m_bullet.GetDDong()).begin(); iter != (m_bullet.GetDDong()).end(); ++iter)
        {
            if (IntersectRect(&rt, &m_player.GetBody(), &(*iter)))
            {
                (m_cDDong.GetDDong()).erase(iter);
                m_isPlaying = false;
                break;
            }
        }
        */
    }
    else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
    {
        m_player.Setup();
        //m_bullet.Setup();
        m_isPlaying = true;
    }
}

void MainGame::Render(HDC hdc)
{
    m_player.Render(hdc);
    char str[128];
    sprintf_s(str, "게임 레벨 : %d", m_gameLvl);
    TextOut(hdc, 10, 10, str, strlen(str));
}
