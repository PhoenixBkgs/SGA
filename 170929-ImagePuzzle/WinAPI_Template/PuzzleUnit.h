#pragma once
#include "ImageKomastar.h"

#define PUZZLE_BORDER 2

class PuzzleUnit
{
    //  VARS
private:
    ImageKomastar*  m_imgSlide;
    RECT            m_imgRect;

    int             m_uId;
    int             m_posId;
    bool            m_isActivate;
    bool            m_isShow;

    UnitSize        m_puzzleInitPos;
    UnitSize        m_puzzleSize;
    UnitSize        m_puzzlePos;
    int             m_puzzleBorder;

public:
    //  FUNCS
private:
public:
    PuzzleUnit();
    ~PuzzleUnit();

    void Start();
    void Update();
    void Render();

    //  GET SET
    void SetPuzzleUid(int Uid) { m_uId = Uid; };
    void SetPuzzlePosId(int PosId) { m_posId = PosId; }
    void SetPuzzleSize(UnitSize Size) { m_puzzleSize = Size; }
    void SetPuzzleInitPos(UnitSize Position) { m_puzzleInitPos = Position; }
    void SetPuzzlePos(UnitSize Position) { m_puzzlePos = Position; }
    void SetPuzzleImage(ImageKomastar* pImage) { m_imgSlide = pImage; }
    void SetPuzzleShow(bool Show) { m_isShow = Show; }
    RECT GetPuzzleRect() { return m_imgRect; }
    UnitSize GetPuzzlePos() { return m_puzzlePos; }
    UnitSize GetPuzzleInitPos() { return m_puzzleInitPos; }
    int GetPuzzleUid() { return m_uId; }
    int GetPuzzlePosId() { return m_posId; }

    void Show() { m_isShow = true; }
    void Hide() { m_isShow = false; }
    bool IsShow() { return m_isShow; }
};