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
    m_comboFactor = 1.0f;
    m_comboCount = 0;
    m_prevUid = -1;
    m_finishCount = 0;
    m_showCount = 15;
    m_gameScore = 0;
    m_clickCount = 0;
    m_isEnd = false;
    m_isMatchFail = false;
    m_hasInsight = false;
    m_isPlaying = false;
    srand((int)time(NULL));
    m_showIdx1 = rand() % MAX_CARD;
    m_showIdx2 = rand() % MAX_CARD;
    m_showIdx3 = rand() % MAX_CARD;
    m_showIdx4 = rand() % MAX_CARD;

    for (int i = 0; i < HALF_CARD; i++)
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

    int row = -1;
    int col = 20;
    for (int i = 0; i < MAX_CARD; i++)
    {
        if (i % col == 0)
        {
            row++;
        }

        RECT rt;
        rt.left = 30 + (IMG_WIDTH + 10) * (i % col);
        rt.top = 30 + (IMG_HEIGHT + 10) * row;
        rt.right = rt.left + IMG_WIDTH;
        rt.bottom = rt.top + IMG_HEIGHT;

        cCard tempCard;
        tempCard.m_rtBody = rt;

        tempCard.m_isFinished = false;
        tempCard.m_isOpen = false;
        tempCard.m_uId = i;
        tempCard.m_cId = i % HALF_CARD;
        
        m_vecCards.push_back(tempCard);
    }

    srand((int)time(NULL));
    //  Shuffle
    for (int i = 0; i < MAX_CARD; i++)
    {
        int idx = rand() % MAX_CARD;

        int exTemp;
        exTemp = m_vecCards[i].m_cId;
        m_vecCards[i].m_cId = m_vecCards[idx].m_cId;
        m_vecCards[idx].m_cId = exTemp;
    }
}

void MainGame::Update()
{
    GameNode::Update();

    if (m_isPlaying)
    {
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
        if (g_pKeyManager->isStayKeyDown(VK_RBUTTON))
        {
            m_hasInsight = true;
        }
        else
        {
            m_hasInsight = false;
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
                    if (m_prevUid == iter->m_uId)
                    {
                        iter->m_isOpen = false;
                        break;
                    }

                    if (m_clickCount == 0 && iter->m_isFinished == false)
                    {
                        m_prevCard = iter._Ptr;
                        m_prevUid = iter->m_uId;
                        m_clickCount++;
                        break;
                    }
                    else
                    {
                        if (m_prevCard->m_cId == iter->m_cId)
                        {
                            iter->m_isFinished = true;
                            m_prevCard->m_isFinished = true;
                            m_gameScore += (int)(10 * m_comboFactor);
                            m_comboFactor *= 1.5f;
                            m_finishCount += 2;
                            m_comboCount++;
                        }
                        else
                        {
                            m_gameScore -= 5;
                            m_comboFactor = 1.0f;
                            m_comboCount = 0;
                            m_isMatchFail = true;
                        }
                        m_clickCount = 0;
                    }
                }
            }
        }

        if (m_finishCount >= MAX_CARD)
        {
            m_isEnd = true;
        }
    }
    else
    {
        if (m_showSleepCnt <= 0)
        {
            m_vecCards[m_showIdx1].m_isOpen = false;
            m_vecCards[m_showIdx2].m_isOpen = false;
            m_vecCards[m_showIdx3].m_isOpen = false;
            m_vecCards[m_showIdx4].m_isOpen = false;
            m_showSleepCnt = 30;
            m_showIdx1 = rand() % MAX_CARD;
            m_showIdx2 = rand() % MAX_CARD;
            m_showIdx3 = rand() % MAX_CARD;
            m_showIdx4 = rand() % MAX_CARD;

            if (m_showCount <= 0)
            {
                m_isPlaying = true;
                if (m_isEnd)
                {
                    Sleep(1000);
                }
            }
            m_showCount--;
        }
        else
        {
            m_vecCards[m_showIdx1].m_isOpen = true;
            m_vecCards[m_showIdx2].m_isOpen = true;
            m_vecCards[m_showIdx3].m_isOpen = true;
            m_vecCards[m_showIdx4].m_isOpen = true;
            m_showSleepCnt--;
        }
    }

    if (m_isEnd)
    {
        m_comboCount = 0;
        m_comboFactor = 1.0f;
        for (auto iter = m_vecCards.begin(); iter != m_vecCards.end(); iter++)
        {
            iter->m_isFinished = false;
            iter->m_isOpen = false;
        }

        //  Shuffle
        for (int i = 0; i < MAX_CARD; i++)
        {
            int idx = rand() % MAX_CARD;

            int exTemp;
            exTemp = m_vecCards[i].m_cId;
            m_vecCards[i].m_cId = m_vecCards[idx].m_cId;
            m_vecCards[idx].m_cId = exTemp;
        }
        m_isEnd = false;
        m_isPlaying = false;
    }
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);

    char infoMsg[100];
    sprintf_s(infoMsg, "GAMESCORE : %d                 COMBO : %d              COMBO FACTOR : %.0f %%", m_gameScore, m_comboCount, m_comboFactor * 100.0f);
    TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));

    for (auto iter = m_vecCards.begin(); iter != m_vecCards.end(); iter++)
    {
        int posX = iter->m_rtBody.left;
        int posY = iter->m_rtBody.top;
        if (iter->m_isOpen)
        {
            m_vecStImages[iter->m_cId].ImageFront->Render(g_hDC, posX, posY);
        }
        else
        {
            m_vecStImages[iter->m_cId].ImageBack->Render(g_hDC, posX, posY);
            if (m_hasInsight)
            {
                char infoMsg[100];
                sprintf_s(infoMsg, "ID : %d", iter->m_cId);
                TextOut(g_hDC, posX, posY, infoMsg, (int)strlen(infoMsg));
            }
        }
    }
}