#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    Start();
}


MainGame::~MainGame()
{
}

void MainGame::Start()
{
    m_gameScore = 0;
    m_clickCount = 0;
    m_isMatchFail = false;

    for (int i = 0; i < MAX_CARD; i++)
    {
        RECT rt;
        rt.left = 10 + IMG_WIDTH * (i % 5);
        rt.top = 30;
        if (i >= 5)
        {
            rt.top += IMG_HEIGHT + 20;
        }
        rt.right = rt.left + 120;
        rt.bottom = rt.top + IMG_HEIGHT;

        Card tCard;
        tCard.ImageFront = new ImageKomastar;
        tCard.ImageFront->Setup(m_imageNames[i % 5].data(), IMG_WIDTH, IMG_HEIGHT);
        tCard.ImageBack = new ImageKomastar;
        tCard.ImageBack->Setup("images/CardBack.bmp", IMG_WIDTH, IMG_HEIGHT);
        tCard.ImageRect = rt;

        tCard.IsFinished = false;
        tCard.IsOpen = false;
        tCard.cardId = i % 5;
        
        m_cards[i] = tCard;
    }

    srand(time(NULL));
    //  Shuffle
    for (int i = 0; i < 10; i++)
    {
        int idx = rand() % 10;

        ImageKomastar* exImg;
        exImg = m_cards[i].ImageFront;
        m_cards[i].ImageFront = m_cards[idx].ImageFront;
        m_cards[idx].ImageFront = exImg;

        int exId;
        exId = m_cards[i].cardId;
        m_cards[i].cardId = m_cards[idx].cardId;
        m_cards[idx].cardId = exId;
    }
}

void MainGame::Update()
{
    GameNode::Update();
    if (m_isMatchFail)
    {
        Sleep(500);
        for (int i = 0; i < MAX_CARD; i++)
        {
            if (m_cards[i].IsFinished == false)
            {
                m_cards[i].IsOpen = false;
            }
        }
        m_isMatchFail = false;
    }

    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        //  마우스 좌클릭
        //  충돌 체크
        for (int i = 0; i < MAX_CARD; i++)
        {
            bool isClicked = m_physicsHelper.PtInsideRect(UnitPos{ (double)g_ptMouse.x, (double)g_ptMouse.y }, m_cards[i].ImageRect);
            if (isClicked)
            {
                m_cards[i].IsOpen = true;
                if (m_clickCount == 0 && m_cards[i].IsFinished == false)
                {
                    m_prevCardIdx = i;
                    m_clickCount++;
                }
                else
                {
                    if (m_cards[m_prevCardIdx].cardId == m_cards[i].cardId)
                    {
                        m_cards[i].IsFinished = true;
                        m_cards[m_prevCardIdx].IsFinished = true;
                        m_gameScore += 10;
                    }
                    else
                    {
                        m_isMatchFail = true;
                    }
                    m_clickCount = 0;
                }
            }
        }
    }
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);

    char infoMsg[100];
    sprintf_s(infoMsg, "GAMESCORE : %d", m_gameScore);
    TextOut(g_hDC, 10, 10, infoMsg, strlen(infoMsg));

    for (int i = 0; i < MAX_CARD; i++)
    {
        if (m_cards[i].IsOpen)
        {
            m_cards[i].ImageFront->Render(g_hDC, m_cards[i].ImageRect.left, m_cards[i].ImageRect.top);
            char infoMsg[100];
            sprintf_s(infoMsg, "ID : %d", m_cards[i].cardId);
            TextOut(g_hDC, m_cards[i].ImageRect.left, m_cards[i].ImageRect.top, infoMsg, strlen(infoMsg));
        }
        else
        {
            m_cards[i].ImageBack->Render(g_hDC, m_cards[i].ImageRect.left, m_cards[i].ImageRect.top);
        }
    }
}