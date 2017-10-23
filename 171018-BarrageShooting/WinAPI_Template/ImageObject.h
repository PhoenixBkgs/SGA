#pragma once
#include "EnumState.h"
class DrawHelper;
class GeometryHelper;
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
    DrawHelper* m_drawHelper;
    GeometryHelper* m_geoHelper;

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

public:
    ImageObject();
    ~ImageObject();

    void SetHelper(DrawHelper* Drawer) { m_drawHelper = Drawer; }

    void Setup(int width, int height);
    void Setup(const char* FileName, int width, int height);

    void Render(HDC hdc);
    void Render(HDC hdc, UnitPos Pos);
    void Render(HDC hdc, int destX, int destY);
    void Render(HDC hdc, int destX, int destY, int destW, int destH);
    void Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcW, int srcH);

    //  FOR ALPHA BLEND
    void SetupForAlphaBlend();
    void Render(HDC hdc, UnitPos DestPos, UnitSize DestSize, int FrameX, int FrameY, double Ratio);
    void Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcW, int srcH, int alpha);
    void Render(HDC hdc, int destX, int destY, int destW, int destH, int srcX, int srcY, int srcW, int srcH, int alpha);
    void Render(HDC hdc, UnitPos KeyPos, double Angle);
    void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);

    //  FOR SPRITES
    void SetupForSprites(int SpritesWidth, int SpritesHeight, int SpritesDelay);
    void SpritesRender(HDC hdc, RECT SpritesBox, BYTE alpha);
    void SpritesRender(HDC hdc, RECT SpritesBox, int FrameX, int FrameY);
    void SpritesRender(HDC hdc, RECT SpritesBox, int FrameX, int FrameY, double Alpha);
    void SpritesRender(HDC hdc, UnitPos Pos, BYTE alpha);
    void SpritesRender(HDC hdc, UnitPos Pos, UnitSize Size, int FrameX, int FrameY);
    void SpritesRender(HDC hdc, UnitPos RightEndPos, UnitSize EachSize, int Number);

    //  FOR TRANSPARENT
    void SetTransColor(bool isTrans, COLORREF transColor);

    //  GET, SET
    HDC GetMemDC() { return m_pImageInfo->hMemDC; }
    int GetWidth() { return m_pImageInfo->nWidth; }
    int GetHeight() { return m_pImageInfo->nHeight; }
    UnitSize GetSize() { return { GetWidth(), GetHeight() }; }
    void SetIsSprites(bool IsSprites) { m_isSprites = IsSprites; }
};

