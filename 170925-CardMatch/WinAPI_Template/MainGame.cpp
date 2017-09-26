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

    for (int i = 0; i < 5; i++)
    {
        ImageKomastar* frontImage = new ImageKomastar;
        ImageKomastar* backImage = new ImageKomastar;

        char filename[MAXCHAR];
        sprintf_s(filename, "images/seq/CardFront_%03d.bmp", i);
        frontImage->Setup(filename, IMG_WIDTH, IMG_HEIGHT);
        backImage->Setup("images/CardBack.bmp", IMG_WIDTH, IMG_HEIGHT);

        tagImage stImage;
        stImage.ImageFront = frontImage;
        stImage.ImageBack = backImage;
        stImage.cId = i;

        m_vecStImages.push_back(stImage);
    }

    for (int i = 0; i < MAX_CARD; i++)
    {
        RECT rt;
        rt.left = 10 + IMG_WIDTH * (i % 5);
        rt.top = 30;
        if (i >= 5)
        {
            rt.top += IMG_HEIGHT + 20;
        }
        rt.right = rt.left + IMG_WIDTH;
        rt.bottom = rt.top + IMG_HEIGHT;

        cCard tempCard;
        tempCard.m_rtBody = rt;

        tempCard.m_isFinished = false;
        tempCard.m_isOpen = false;
        tempCard.m_cId = i % 5;
        
        m_vecCards.push_back(tempCard);
    }

    srand((int)time(NULL));
    //  Shuffle
    for (int i = 0; i < 10; i++)
    {
        int idx = rand() % 10;

        int exTemp;
        exTemp = m_vecCards[i].m_cId;
        m_vecCards[i].m_cId = m_vecCards[idx].m_cId;
        m_vecCards[idx].m_cId = exTemp;
    }
}

void MainGame::Update()
{
    GameNode::Update();
    if (m_isMatchFail)
    {
        Sleep(500);
        for (auto iter = m_vecCards.begin(); iter != m_vecCards.end(); iter++)
        {
            if (iter->m_isFinished == false)
            {
                iter->m_isOpen = false;
            }
        }
        m_isMatchFail = false;
    }

    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        //  마우스 좌클릭
        //  충돌 체크
        for (auto iter = m_vecCards.begin(); iter != m_vecCards.end(); iter++)
        {
            bool isClicked = m_physicsHelper.PtInsideRect(UnitPos{ (double)g_ptMouse.x, (double)g_ptMouse.y }, iter->m_rtBody);
            if (isClicked)
            {
                iter->m_isOpen = true;
                if (m_clickCount == 0 && iter->m_isFinished == false)
                {
                    m_prevCard = iter._Ptr;
                    m_clickCount++;
                }
                else
                {
                    if (m_prevCard->m_cId == iter->m_cId)
                    {
                        iter->m_isFinished = true;
                        m_prevCard->m_isFinished = true;
                        m_gameScore += 10;
                    }
                    else
                    {
                        m_gameScore -= 5;
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
    TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));

    for (auto iter = m_vecCards.begin(); iter != m_vecCards.end(); iter++)
    {
        int posX = iter->m_rtBody.left;
        int posY = iter->m_rtBody.top;
        if (iter->m_isOpen)
        {
            m_vecStImages[iter->m_cId].ImageFront->Render(g_hDC, posX, posY);
            char infoMsg[100];
            sprintf_s(infoMsg, "ID : %d", iter->m_cId);
            TextOut(g_hDC, posX, posY, infoMsg, (int)strlen(infoMsg));
        }
        else
        {
            m_vecStImages[iter->m_cId].ImageBack->Render(g_hDC, posX, posY);
        }
    }
}