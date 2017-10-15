#pragma once
#include "EnumState.h"
class Draw2DKomastar;
class ImageKomastar
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
            btLoadType = LOAD_EMPTY;

        }
    }  IMAGE_INFO, *LPIMAGE_INFO;

private:
    Draw2DKomastar* m_drawHelper;

    LPIMAGE_INFO    m_pImageInfo;
    char*           m_szFileName;
    bool            m_isTrans;
    COLORREF        m_transColor;  //  255, 0, 255 = TRANSPARENT COLOR (MAGENTA)

    //  FOR ALPHA BLEND
    BLENDFUNCTION   m_stBlendFunc;
    LPIMAGE_INFO	m_pBlendImage;

    //  FOR SPRITES
    bool            m_isSprites;
    int             m_spritesWidth;
    int             m_spritesHeight;
    int             m_currFrameX;
    int             m_currFrameY;
    int             m_maxFrameX;
    int             m_maxFrameY;
    int             m_spritesDelayCount;
    int             m_spritesInitDelay;

public:
    ImageKomastar();
    ~ImageKomastar();

    void SetHelper(Draw2DKomastar* Drawer) { m_drawHelper = Drawer; }

    void Setup(int width, int height);
    void Setup(const char* FileName, int width, int height);

    void Render(HDC hdc);
    void Render(HDC hdc, int destX, int destY);
    void Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcW, int srcH);

    //  FOR ALPHA BLEND
    void SetupForAlphaBlend();
    void Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcW, int srcH, int alpha);
    void Render(HDC hdc, int destX, int destY, int destW, int destH, int srcX, int srcY, int srcW, int srcH, int alpha);
    void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);

    //  FOR SPRITES
    void SetupForSprites(int MaxFrameX, int MaxFrameY, int SpritesWidth, int SpritesHeight, int SpritesDelay);
    void SpritesRender(HDC hdc, RECT SpritesBox, BYTE alpha);

    //  FOR TRANSPARENT
    void SetTransColor(bool isTrans, COLORREF transColor);

    //  GET, SET
    HDC GetMemDC() { return m_pImageInfo->hMemDC; }
    int GetWidth() { return m_pImageInfo->nWidth; }
    int GetHeight() { return m_pImageInfo->nHeight; }
    void SetIsSprites(bool IsSprites) { m_isSprites = IsSprites; }
    int GetFrameX() { return m_currFrameX; }
    int GetFrameY() { return m_currFrameY; }
    void SetFrameX(int FrameX) { m_currFrameX = FrameX; }
    void SetFrameY(int FrameY) { m_currFrameY = FrameY; }
    int GetMaxFrameX() { return m_maxFrameX; }
    int GetMaxFrameY() { return m_maxFrameY; }
    void Refresh();
};

