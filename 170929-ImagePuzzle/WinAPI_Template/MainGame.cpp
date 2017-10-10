#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_img = new ImageKomastar;
    m_img->Setup("images/hots-splash-img-alpha.bmp", 1200, 600, true, MAGENTA_COLOR);

    Start();
    m_txtPosY = W_HEIGHT * 0.33f;
    m_moveCount = 0;
    m_clearScreenOpacity = 5.0f;
    m_shuffleIdx = MAX_PUZZLE_PCS - 1;
    m_isClear = false;
    m_isPlaying = false;
    m_isShowImage = false;
    m_isShuffling = true;
    srand((int)time(NULL) * 50 * rand());
}


MainGame::~MainGame()
{
    delete m_img;
}

void MainGame::Start()
{
    m_marginLeft = (W_WIDTH - (COL_COUNT * PUZZLE_SIZE)) * 0.5;
    m_marginTop =  (W_HEIGHT - (ROW_COUNT * PUZZLE_SIZE)) * 0.5;

    int rowCnt = -1;
    for (int i = 0; i < MAX_PUZZLE_PCS; i++)
    {
        if (i % COL_COUNT == 0)
        {
            rowCnt++;
        }
        PuzzleUnit unit;
        unit.SetPuzzleImage(m_img);
        unit.SetPuzzleInitPos(UnitSize{ (i % COL_COUNT) * PUZZLE_SIZE, rowCnt * PUZZLE_SIZE });
        unit.SetPuzzleUid(i);
        unit.SetPuzzlePosId(i);
        unit.SetPuzzlePos(UnitSize{ (i % COL_COUNT) * PUZZLE_SIZE + m_marginLeft, rowCnt * PUZZLE_SIZE  + m_marginTop });
        unit.SetPuzzleSize(UnitSize{ PUZZLE_SIZE, PUZZLE_SIZE });
        unit.Start();
        unit.Update();
        m_vecPuzzle.push_back(unit);
    }
    m_vecPuzzle[MAX_PUZZLE_PCS - 1].Hide();
}

void MainGame::Update()
{
    GameNode::Update();
    if (m_shuffleCount < SHUFFLE_LIMITER)
    {
        PuzzleMove(-1);
        Sleep(10);
        m_shuffleCount++;
    }
    else
    {
        m_isShuffling = false;
        m_isPlaying = true;
    }
    
    if (m_isPlaying)
    {
        if (m_isClear)
        {

        }
        else
        {
            MatchChecker();
            PlayerController();
        }
    }
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);

    for (auto iter = m_vecPuzzle.begin(); iter != m_vecPuzzle.end(); iter++)
    {
        iter->Render();
    }

    if (m_isShuffling)
    {
        PatBlt(g_hDC, 0, (int)(W_HEIGHT * 0.5) - 100, W_WIDTH, 100, BLACKNESS);
        m_drawHelper.DrawCenterText("Å¸ÀÏ ¼¯´Â Áß...", 100, (int)(W_HEIGHT * 0.33) + 50, _RGBA{ 200, 200, 200, 0 }, "Consolas");
    }

    if (m_isShowImage)
    {
        m_img->Render(g_hDC, m_marginLeft, m_marginTop, 0, 0, PUZZLE_SIZE * COL_COUNT, PUZZLE_SIZE * ROW_COUNT);
    }

    if (m_isClear)
    {
        PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);

        m_img->Render(g_hDC, m_marginLeft, m_marginTop, 0, 0, PUZZLE_SIZE * COL_COUNT, PUZZLE_SIZE * ROW_COUNT, m_clearScreenOpacity);
        m_drawHelper.DrawCenterText("COMPLETE !!!", 100, m_txtPosY, _RGBA{ 50, 50, 50, 0 }, "Consolas");
        m_isPlaying = false;
        m_isShowImage = false;

        m_clearScreenOpacity += (255.0f - m_clearScreenOpacity) * 0.01f;
        if ((int)m_clearScreenOpacity >= 255)
        {
            m_clearScreenOpacity = 255.0f;
        }

        m_txtPosY += ((0.0f - m_txtPosY) * 0.03f);
        if (m_txtPosY <= 0.0f)
        {
            m_txtPosY = 0.0f;
        }
    }

    char infoMsg[100];
    sprintf_s(infoMsg, "¸ÂÃá ÆÛÁñ °³¼ö : %d", m_matchCount, m_moveCount);
    TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));
    sprintf_s(infoMsg, "¿òÁ÷ÀÎ È½¼ö : %d", m_moveCount);
    TextOut(g_hDC, W_WIDTH - 300, 10, infoMsg, (int)strlen(infoMsg));
}

void MainGame::PlayerController()
{
    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        for (auto iter = m_vecPuzzle.begin(); iter != m_vecPuzzle.end(); iter++)
        {
            if (PtInRect(&iter->GetPuzzleRect(), g_ptMouse))
            {
                int tPosId = iter->GetPuzzlePosId();
                if (tPosId - 1 >= 0 && (tPosId % COL_COUNT != 0))
                {
                    if (iter->IsShow() == true && (iter - 1)->IsShow() == false)
                    {
                        PuzzleExchange(iter._Ptr, (iter - 1)._Ptr);
                    }
                }
                if ((tPosId + 1 < MAX_PUZZLE_PCS) && (tPosId % COL_COUNT != COL_COUNT - 1))
                {
                    if (iter->IsShow() == true && (iter + 1)->IsShow() == false)
                    {
                        PuzzleExchange(iter._Ptr, (iter + 1)._Ptr);
                    }
                }

                if (tPosId - COL_COUNT >= 0)
                {
                    if (iter->IsShow() == true && (iter - COL_COUNT)->IsShow() == false)
                    {
                        PuzzleExchange(iter._Ptr, (iter - COL_COUNT)._Ptr);
                    }
                }

                if (tPosId + COL_COUNT < MAX_PUZZLE_PCS)
                {
                    if (iter->IsShow() == true && (iter + COL_COUNT)->IsShow() == false)
                    {
                        PuzzleExchange(iter._Ptr, (iter + COL_COUNT)._Ptr);
                    }
                }
            }
        }
    }

    
    if (g_pKeyManager->isOnceKeyDown(VK_LEFT))
    {
        PuzzleMove(0);
    }
    else if (g_pKeyManager->isOnceKeyDown(VK_RIGHT))
    {
        PuzzleMove(1);
    }
    else if (g_pKeyManager->isOnceKeyDown(VK_UP))
    {
        PuzzleMove(2);
    }
    else if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
    {
        PuzzleMove(3);
    }
    
    if (g_pKeyManager->isStayKeyDown(VK_RBUTTON) ||
        g_pKeyManager->isStayKeyDown(VK_SPACE))
    {
        //  show target image
        m_isShowImage = true;
    }
    else
    {
        m_isShowImage = false;
    }
}

void MainGame::SystemController()
{
}

void MainGame::PuzzleMove(int Direction)
{
    int randDir = rand() % 4;
    if (Direction >= 0)
    {
        randDir = Direction;
        m_moveCount++;
    }
    switch (randDir)
    {
    case 0: //  swap left
    {
        if (m_shuffleIdx - 1 >= 0 && (m_shuffleIdx % COL_COUNT != 0))
        {
            PuzzleExchange(&m_vecPuzzle[m_shuffleIdx], &m_vecPuzzle[m_shuffleIdx - 1]);
            m_shuffleIdx = m_shuffleIdx - 1;
        }
        break;
    }
    case 1: //  swap right
    {
        if ((m_shuffleIdx + 1 < MAX_PUZZLE_PCS) && (m_shuffleIdx % COL_COUNT != COL_COUNT - 1))
        {
            PuzzleExchange(&m_vecPuzzle[m_shuffleIdx], &m_vecPuzzle[m_shuffleIdx + 1]);
            m_shuffleIdx = m_shuffleIdx + 1;
        }
        break;
    }
    case 2: //  swap up
    {
        if (m_shuffleIdx - COL_COUNT >= 0)
        {
            PuzzleExchange(&m_vecPuzzle[m_shuffleIdx], &m_vecPuzzle[m_shuffleIdx - COL_COUNT]);
            m_shuffleIdx = m_shuffleIdx - COL_COUNT;
        }
        break;
    }
    case 3: //  swap down
    {
        if (m_shuffleIdx + COL_COUNT < MAX_PUZZLE_PCS)
        {
            PuzzleExchange(&m_vecPuzzle[m_shuffleIdx], &m_vecPuzzle[m_shuffleIdx + COL_COUNT]);
            m_shuffleIdx = m_shuffleIdx + COL_COUNT;
        }
        break;
    }
    }
}

void MainGame::PuzzleExchange(PuzzleUnit * Puzzle1, PuzzleUnit * Puzzle2)
{
    UnitSize tPos = Puzzle1->GetPuzzleInitPos();
    Puzzle1->SetPuzzleInitPos(Puzzle2->GetPuzzleInitPos());
    Puzzle2->SetPuzzleInitPos(tPos);

    bool tShow = Puzzle1->IsShow();
    Puzzle1->SetPuzzleShow(Puzzle2->IsShow());
    Puzzle2->SetPuzzleShow(tShow);

    int tUid = Puzzle1->GetPuzzleUid();
    Puzzle1->SetPuzzleUid(Puzzle2->GetPuzzleUid());
    Puzzle2->SetPuzzleUid(tUid);
}

void MainGame::MatchChecker()
{
    int solPosId = 0;
    m_matchCount = 0;
    for (auto iter = m_vecPuzzle.begin(); iter != m_vecPuzzle.end(); iter++)
    {
        int currUid = iter->GetPuzzleUid();
        if (currUid == solPosId)
        {
            m_matchCount++;
        }
        solPosId++;
    }

    if (m_matchCount == MAX_PUZZLE_PCS)
    {
        m_isClear = true;
    }
}
