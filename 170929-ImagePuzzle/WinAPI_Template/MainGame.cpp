#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_img = new ImageKomastar;
    m_img->Setup("images/hots-splash-img.bmp", 1200, 600, true, MAGENTA_COLOR);

    Start();
    m_shuffleIdx = MAX_PUZZLE_PCS - 1;
    m_isPlaying = false;
    srand((int)time(NULL) * 50 * rand());
}


MainGame::~MainGame()
{
    delete m_img;
}

void MainGame::Start()
{
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
        unit.SetPuzzlePos(UnitSize{ (i % COL_COUNT) * PUZZLE_SIZE, rowCnt * PUZZLE_SIZE });
        unit.SetPuzzleSize(UnitSize{ PUZZLE_SIZE, PUZZLE_SIZE });
        unit.Start();
        unit.Update();
        m_vecPuzzle.push_back(unit);
    }
    m_vecPuzzle[MAX_PUZZLE_PCS - 1].Hide();

    PuzzleShuffle();
}

void MainGame::Update()
{
    GameNode::Update();
    if (m_shuffleCount < SHUFFLE_LIMITER)
    {
        PuzzleShuffle();
        Sleep(100);
    }
    else
    {
        m_shuffleCount++;
    }

    if (m_isPlaying)
    {
        PlayerController();
    }
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);

    for (auto iter = m_vecPuzzle.begin(); iter != m_vecPuzzle.end(); iter++)
    {
        iter->Render();
    }
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
}

void MainGame::SystemController()
{
}

void MainGame::PuzzleShuffle()
{
    int randDir = rand() % 4;
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
