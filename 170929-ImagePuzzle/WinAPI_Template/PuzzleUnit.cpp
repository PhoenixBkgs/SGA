#include "stdafx.h"
#include "PuzzleUnit.h"


PuzzleUnit::PuzzleUnit()
{
    m_isActivate = false;
    m_puzzleBorder = PUZZLE_BORDER;
}


PuzzleUnit::~PuzzleUnit()
{
}

void PuzzleUnit::Start()
{
    m_isActivate = true;
}

void PuzzleUnit::Update()
{
    if (m_isActivate)
    {
        m_imgRect.left = m_puzzlePos.w;
        m_imgRect.right = m_imgRect.left + m_puzzleSize.w;
        m_imgRect.top = m_puzzlePos.h;
        m_imgRect.bottom = m_imgRect.top + m_puzzleSize.h;
    }
}

void PuzzleUnit::Render()
{
    m_imgSlide->Render(g_hDC, m_puzzlePos.w + m_puzzleSize.w, m_puzzlePos.h + m_puzzleSize.h,
                              m_puzzlePos.w, m_puzzlePos.h,
                              m_puzzleSize.w - m_puzzleBorder, m_puzzleSize.h - m_puzzleBorder);
}
