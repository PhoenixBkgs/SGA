#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_isSetup = false;
    m_isPlaying = false;
    Setup();
}


MainGame::~MainGame()
{
}

void MainGame::Update()
{
    GameNode::Update();
    if (m_isPlaying)
    {
        

        if (m_playerLife < 1)
        {
            m_isPlaying = false;
        }

        if (m_isTargetUp)
        {
            m_vecStTarget[m_targetUpIdx].isUp = true;
            m_targetUpTime--;
        }
        else
        {
            m_isClickable = true;
            m_targetUpDelay--;
        }

        if (m_targetUpTime < 0)
        {
            if (m_vecStTarget[m_targetUpIdx].isUp)
            {
                m_playerLife--;
            }

            for (auto iter = m_vecStTarget.begin(); iter != m_vecStTarget.end(); iter++)
            {
                iter->isUp = false;
            }
            m_targetUpTime = TARGET_UP_TIME;
            m_isTargetUp = false;
            srand(time(NULL) * m_targetUpIdx * m_playerLife * m_gameScore);
            m_targetUpIdx = rand() % 9;
        }

        if (m_targetUpDelay < 0)
        {
            //  delay
            m_isTargetUp = true;
            m_targetUpDelay = TARGET_UP_DELAY;
        }
        else
        {
        }

        if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
        {
            for (auto iter = m_vecStTarget.begin(); iter != m_vecStTarget.end(); ++iter)
            {
                bool isClicked = PtInRect(&iter->rtBody, g_ptMouse);
                if (isClicked && m_isClickable)
                {
                    if (iter->isUp)
                    {
                        m_gameScore += iter->score;
                        iter->isUp = false;
                        m_isTargetUp = false;
                        m_isHit = true;
                        srand(time(NULL) * m_targetUpIdx * m_playerLife * m_gameScore);
                        m_targetUpIdx = rand() % 9;
                        m_maxDelay--;
                        if (m_maxDelay <= 50)
                        {
                            m_maxDelay = 50;
                        }
                        m_maxUpTime--;
                        if (m_maxUpTime <= 50)
                        {
                            m_maxUpTime = 50;
                        }
                        break;
                    }
                }
            }
            if (m_isHit)
            {
                m_isHit = false;
                m_isClickable = true;
            }
            else
            {
                m_playerLife--;
                m_isClickable = false;
            }
        }
    }
    else
    {
        if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
        {
            m_isPlaying = true;
        }
    }
}

void MainGame::Render(HDC hdc)
{
    Rectangle(hdc, 0, 0, WINSIZEX, WINSIZEY);
    char infoMsg[100];
    sprintf_s(infoMsg, "Á¡¼ö : %d         Life : %d", m_gameScore, m_playerLife);
    TextOut(hdc, 10, 10, infoMsg, strlen(infoMsg));

    for (auto iter = m_vecStTarget.begin(); iter != m_vecStTarget.end(); iter++)
    {
        if (iter->isUp)
        {
            Rectangle(hdc, iter->rtBody.left, iter->rtBody.top, iter->rtBody.right, iter->rtBody.bottom);
            FillRect(hdc, &iter->rtBody, m_colorBlack);
        }
    }

    for (auto iter = m_vecBar.begin(); iter != m_vecBar.end(); iter++)
    {
        Rectangle(hdc, iter->rtBody.left, iter->rtBody.top, iter->rtBody.right, iter->rtBody.bottom);
        FillRect(hdc, &iter->rtBody, iter->brush);
    }
}

void MainGame::Setup()
{
    if (m_isSetup)
    {

    }
    else
    {
        m_gameLevel = 1;
        m_gameScore = 0;
        m_playerLife = 10;
        m_maxDelay = TARGET_UP_DELAY;
        m_maxUpTime = TARGET_UP_TIME;
        m_targetUpDelay = TARGET_UP_DELAY;
        m_targetUpTime = TARGET_UP_TIME;
        m_currGameState = GS_READY;
        m_colorBlack = CreateSolidBrush(RGB(0, 0, 0));
        m_colorWhite = CreateSolidBrush(RGB(255, 255, 255));
        CreateTargets();
        m_isSetup = true;
        m_isClickable = true;
        m_targetUpIdx = rand() % 9;
    }
}

void MainGame::CreateTargets()
{
    for (int i = 0; i < 9; i++)
    {
        Target stTarget;
        RECT tRect;
        POINT targetPos;
        int tWidth = 0;
        int tHeight = 80;
        int score = 0;
        int marginX = (int)(WINSIZEX * 0.25);
        int marginY = (int)(WINSIZEY * 0.25);
        targetPos.x = marginX * ((i % 3) + 1);

        if (i < 3)
        {
            targetPos.y = marginY;
            tWidth = 40;
            score = 5;
        }
        else if (i < 6)
        {
            targetPos.y = marginY * 2;
            tWidth = 80;
            score = 3;
        }
        else
        {
            targetPos.y = marginY * 3;
            tWidth = 120;
            score = 1;
        }

        tRect.left = targetPos.x - tWidth * 0.5;
        tRect.right = tRect.left + tWidth;
        tRect.top = targetPos.y - tHeight;
        tRect.bottom = targetPos.y;
        stTarget.rtBody = tRect;
        stTarget.isUp = false;
        stTarget.score = score;
        stTarget.brush = m_colorWhite;

        m_vecStTarget.push_back(stTarget);

        Target bar;
        bar.brush = m_colorBlack;
        targetPos.x -= 50;
        bar.rtBody.left = tRect.left - 10;
        bar.rtBody.right = tRect.right + 10;
        bar.rtBody.top = tRect.bottom - 20;
        bar.rtBody.bottom = tRect.bottom;
        m_vecBar.push_back(bar);
    }
}