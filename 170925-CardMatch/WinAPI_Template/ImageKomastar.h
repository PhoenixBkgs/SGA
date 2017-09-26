#pragma once
#include "EnumState.h"

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
    LPIMAGE_INFO m_stImageInfo;
    char* m_szFileName;
    bool m_isTrans;
    COLORREF m_transColor;  //  255, 0, 255 = TRANSPARENT COLOR (MAGENTA)

public:
    ImageKomastar();
    ~ImageKomastar();

    void Setup(int width, int height);
    void Setup(const char* FileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
    void Render(HDC hdc);
    void Render(HDC hdc, int destX, int destY);
    void SetTransColor(bool isTrans, COLORREF transColor);

    HDC GetMemDC() { return m_stImageInfo->hMemDC; }

};

