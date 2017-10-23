#pragma once
class ImageObject
{
public:
    typedef struct tagimage
    {
        DWORD   resID;
        HDC     hMemDC;
        HBITMAP hBit;
        HBITMAP hOldBit;
        int     nWidth;
        int     nHeight;
        BYTE    btLoadType;

        tagimage()
        {
            resID = 0;
            hMemDC = NULL;
            hBit = NULL;
            hOldBit = NULL;
            nWidth = 0;
            nHeight = 0;
            btLoadType = 0;

        }
    }  IMAGE_INFO, *LPIMAGE_INFO;

private:
    LPIMAGE_INFO    m_pImageInfo;
    char*           m_szFileName;
    bool            m_isTrans;
    COLORREF        m_transColor;  //  255, 0, 255 = TRANSPARENT COLOR (MAGENTA)

    //  FOR ALPHA BLEND
    BLENDFUNCTION   m_stBlendFunc;
    LPIMAGE_INFO	m_pBlendImage;

    //  FOR SPRITES
    int             m_spritesWidth;
    int             m_spritesHeight;


public:
#pragma region GET
    HDC GetMemDC() { return m_pImageInfo->hMemDC; }
    int GetWidth() { return m_pImageInfo->nWidth; }
    int GetHeight() { return m_pImageInfo->nHeight; }
    UnitSize GetSize() { return { GetWidth(), GetHeight() }; }
#pragma endregion
#pragma region SET
    void SetSpritesSize(UnitSize Size) { m_spritesWidth = Size.w, m_spritesHeight = Size.h; }
#pragma endregion

public:
#pragma region CONSTRUCTOR
    ImageObject();
    ~ImageObject();
#pragma endregion

#pragma region SETUP
    void Setup(int width, int height);
    void Setup(const char* FileName, int width, int height);
#pragma endregion

//  BitBlt
#pragma region FAST_RENDER
    void FastRender(HDC hdc);
    void FastRender(HDC hdc, UnitPos DestPos);
    void FastRender(HDC hdc, UnitPos DestPos, UnitPos SrcPos);
#pragma endregion

//  TransparentBlt
#pragma region TRANSPARENT_RENDER
    void TransRender(HDC hdc);
#pragma endregion

//  AlphaBlend
#pragma region ALPHA_RENDER

#pragma endregion

//  Sprites
#pragma region SPRITES_RENDER
    void SpritesRender(HDC hdc, RECT SpritesBox, int FrameX, int FrameY, double Alpha);
    void SpritesRender(HDC hdc, UnitPos DestPos, UnitSize DestSize, int FrameX, int FrameY, double Alpha);
    void SpritesRender(HDC hdc, UnitPos RightEndPos, UnitSize EachSize, int Number, double Alpha);
    void SpritesRender(HDC hdc, UnitPos DestPos, UnitSize DestSize, UnitSize SrcSize, int FrameX, int FrameY, double Alpha);
#pragma endregion

//  SPECIAL
#pragma region SPECIAL
    void Render(HDC hdc, UnitPos KeyPos, double Angle);
#pragma endregion

    void Render(HDC hdc, UnitPos Pos);
    void Render(HDC hdc, int destX, int destY);
    void Render(HDC hdc, int destX, int destY, int destW, int destH);
    void Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcW, int srcH);

    //  FOR ALPHA BLEND
    void Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcW, int srcH, int alpha);
    void Render(HDC hdc, int destX, int destY, int destW, int destH, int srcX, int srcY, int srcW, int srcH, int alpha);
    void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);


};

