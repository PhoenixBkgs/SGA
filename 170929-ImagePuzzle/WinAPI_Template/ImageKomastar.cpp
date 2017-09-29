#include "stdafx.h"
#include "ImageKomastar.h"


ImageKomastar::ImageKomastar()
    :m_stImageInfo(NULL), m_szFileName(NULL), m_isTrans(false), m_transColor(RGB(0, 0, 0))
{
}


ImageKomastar::~ImageKomastar()
{
    if (m_stImageInfo)
    {
        SelectObject(m_stImageInfo->hMemDC, m_stImageInfo->hOldBit);
        DeleteObject(m_stImageInfo->hBit);
        DeleteDC(m_stImageInfo->hMemDC);

        if (m_szFileName)
        {
            delete m_szFileName;
        }
        delete m_stImageInfo;
    }
}

void ImageKomastar::Setup(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    m_stImageInfo = new IMAGE_INFO;
    m_stImageInfo->btLoadType = LOAD_EMPTY;
    m_stImageInfo->resID = 0;
    m_stImageInfo->hMemDC = CreateCompatibleDC(hdc);
    m_stImageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    m_stImageInfo->hOldBit = (HBITMAP)SelectObject(m_stImageInfo->hMemDC, m_stImageInfo->hBit);
    m_stImageInfo->nWidth = width;
    m_stImageInfo->nHeight = height;

    ReleaseDC(g_hWnd, hdc);
}

void ImageKomastar::Setup(const char * FileName, int width, int height, bool isTrans, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    m_stImageInfo = new IMAGE_INFO;
    m_stImageInfo->btLoadType = LOAD_FILE;
    m_stImageInfo->resID = 0;
    m_stImageInfo->hMemDC = CreateCompatibleDC(hdc);
    m_stImageInfo->hBit = (HBITMAP)LoadImage(g_hInst, FileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    m_stImageInfo->hOldBit = (HBITMAP)SelectObject(m_stImageInfo->hMemDC, m_stImageInfo->hBit);
    m_stImageInfo->nWidth = width;
    m_stImageInfo->nHeight = height;

    int len = (int)strlen(FileName);
    m_szFileName = new char[len + 1];
    strcpy_s(m_szFileName, len + 1, FileName);

    m_isTrans = isTrans;
    m_transColor = transColor;

    ReleaseDC(g_hWnd, hdc);
}

void ImageKomastar::Render(HDC hdc)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc, 0, 0, m_stImageInfo->nWidth, m_stImageInfo->nHeight, m_stImageInfo->hMemDC, 0, 0, m_stImageInfo->nWidth, m_stImageInfo->nHeight, m_transColor);
    }
    else
    {
        BitBlt(hdc, 0, 0, m_stImageInfo->nWidth, m_stImageInfo->nHeight, m_stImageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

void ImageKomastar::Render(HDC hdc, int destX, int destY)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc, destX, destY, m_stImageInfo->nWidth, m_stImageInfo->nHeight, m_stImageInfo->hMemDC, 0, 0, m_stImageInfo->nWidth, m_stImageInfo->nHeight, m_transColor);
    }
    else
    {
        BitBlt(hdc, destX, destY, m_stImageInfo->nWidth, m_stImageInfo->nHeight, m_stImageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

void ImageKomastar::Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcW, int srcH)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc, destX, destY, srcW, srcH, m_stImageInfo->hMemDC, srcX, srcY, srcW, srcH, m_transColor);
    }
    else
    {
        BitBlt(hdc, destX, destY, srcW, srcH, m_stImageInfo->hMemDC, srcX, srcY, SRCCOPY);
    }
}

void ImageKomastar::SetTransColor(bool isTrans, COLORREF transColor)
{
    m_isTrans = isTrans;
    m_transColor = transColor;
}
