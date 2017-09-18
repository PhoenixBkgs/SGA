#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::Update()
{
    GameNode::Update();
    InputModule();
    switch (m_currGameState)
    {
    case GS_READY:
        //  RESET
        break;
    case GS_PLAYING:
        PlayGame();
        break;
    case GS_CLEAR:

        break;
    case GS_GAMEOVER:
        //  SELECT NEXT STEP
        break;
    case GS_END:
        //  GAME TERMINATION
        break;
    default:
        break;
    }
}

void MainGame::Render(HDC hdc)
{
    for (int i = 0; i < m_entireTargetCount; i++)
    {
        ShootingTarget target;
        int margin = (int)(WINSIZEY * 0.25);
        if (i < 3)
        {
            target.SetTargetSize(TS_SMALL);
        }
        else if (i < 6)
        {
            target.SetTargetSize(TS_MEDIUM);
        }
        else
        {
            target.SetTargetSize(TS_LARGE);
        }
        target.SetTagetUpFlag(false);
        //target.SetTargetPos(POINT);
        target.CreateTargetRect(&hdc);
    }
}

void MainGame::SetCheatMode(E_CHEAT_MODE CheatCode)
{
    switch (CheatCode)
    {
    case CM_SHOTGUN:
        m_cheatMode.flip(3);
        break;
    case CM_BIGHEAD:
        m_cheatMode.flip(2);
        break;
    case CM_CHROMIE:
        m_cheatMode.flip(1);
        break;
    case CM_JAINA:
        m_cheatMode.flip(0);
        break;
    }
}

void MainGame::InputModule()
{
    if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
    {
        switch (m_currGameState)
        {
        case GS_READY:
            m_currGameState = GS_PLAYING;
            break;
        case GS_PLAYING:
            break;
        case GS_CLEAR:
            m_currGameState = GS_READY;
            break;
        case GS_GAMEOVER:
            m_currGameState = GS_READY;
            break;
        case GS_END:
            break;
        }
    }

    if (g_pKeyManager->isOnceKeyDown('S'))
    {
        SetCheatMode(CM_SHOTGUN);
    }
    else if (g_pKeyManager->isOnceKeyDown('B'))
    {
        SetCheatMode(CM_BIGHEAD);
    }
    else if (g_pKeyManager->isOnceKeyDown('C'))
    {
        SetCheatMode(CM_CHROMIE);
    }
    else if (g_pKeyManager->isOnceKeyDown('J'))
    {
        SetCheatMode(CM_JAINA);
    }
}

void MainGame::Setup()
{
    m_gameLevel = 1;
    m_gameScore = 0;
    m_playerLife = 10;
    m_map.SetShootingGallery(3, 3, 3);
    m_currGameState = GS_READY;

    m_entireTargetCount = m_map.GetEntireTargetCount();

}

void MainGame::PlayGame()
{
    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        TargetHitChecker();
    }
}

void MainGame::TargetHitChecker()
{
    //  마우스 위치
    //  RECT 와 비교
    RECT ptRect;
    RECT tRect;
    ptRect = { g_ptMouse.x, g_ptMouse.y, g_ptMouse.x + 1, g_ptMouse.y + 1 };

    for (auto iter = m_map.m_vecTarget.begin(); iter != m_map.m_vecTarget.end(); iter++)
    {
        if (IntersectRect(&tRect, &ptRect, &iter->GetTargetRect()))
        {
            //  HIT
            m_isHit = true;
        }
    }
}
