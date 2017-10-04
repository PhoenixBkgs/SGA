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
    bool            m_isActivate;
    bool            m_isShow;

    string          m_imgFilename;
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
    void SetImgFilename(string Filename) { m_imgFilename = Filename; }
    void SetPuzzleSize(UnitSize Size) { m_puzzleSize = Size; }
    void SetPuzzlePos(UnitSize Position) { m_puzzlePos = Position; }
    void SetPuzzleImage(ImageKomastar* pImage) { m_imgSlide = pImage; }
};