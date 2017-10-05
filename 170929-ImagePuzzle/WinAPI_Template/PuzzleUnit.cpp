#include "stdafx.h"
#include "PuzzleUnit.h"


PuzzleUnit::PuzzleUnit()
{
    m_isActivate = false;
    m_puzzleBorder = PUZZLE_BORDER;
    m_isShow = false;
}


PuzzleUnit::~PuzzleUnit()
{
}

void PuzzleUnit::Start()
{
    m_isActivate = true;
    m_isShow = true;
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
    if (m_isShow)
    {
        m_imgSlide->Render(g_hDC, m_puzzlePos.w, m_puzzlePos.h,
                                  m_puzzleInitPos.w, m_puzzleInitPos.h,
                                  m_puzzleSize.w - m_puzzleBorder, m_puzzleSize.h - m_puzzleBorder);
    }

#ifdef _DEBUG
    char infoMsg[100];
    sprintf_s(infoMsg, "ID : %d", m_uId);
    TextOut(g_hDC, m_puzzlePos.w, m_puzzlePos.h, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}
