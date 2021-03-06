#pragma once
#include "SingletonBase.h"

#define g_pDrawHelper DrawHelper::GetInstance()
struct tagTextBoxInfo
{
    bool    IsVisibleBox;
    _RGBA   FontColor;
    _RGBA   BoxColor;
    string  FontName;
};

class DrawHelper : public SingletonBase<DrawHelper>
{
private:
    HBRUSH*     m_pBrushRed;
    HBRUSH*     m_pBrushGreen;
    HBRUSH*     m_pBrushBlue;

public:
    tagTextBoxInfo  m_textBoxInfo;

public:
    DrawHelper();
    ~DrawHelper();

#pragma region SET
    void    SetColor(_RGBA FontColor, _RGBA BoxColor) { m_textBoxInfo.FontColor = FontColor; m_textBoxInfo.BoxColor = BoxColor; }
    void    SetBoxVisible() { m_textBoxInfo.IsVisibleBox = true; }
    void    SetBoxInvisible() { m_textBoxInfo.IsVisibleBox = false; }
#pragma endregion

    bool DrawLine2D(UnitPos Pos1, UnitPos Pos2, int PenWidth, int ColorCode);
    void DrawBoxLine2D(RECT rt, int LineWidth, int ColorCode);
    RECT MakeRect(UnitPos Pos, UnitSize Size);

    void DrawTextBox(HDC hdc, RECT TxtBox, string TextString);

    UnitSize    GetSizeFromRect(RECT Rect);
    UnitPos     GetPosFromRect(RECT Rect);
};