#include "stdafx.h"
#include "ImageKomastar.h"


ImageKomastar::ImageKomastar()
    :m_pImageInfo(NULL), m_szFileName(NULL), m_isTrans(false), m_transColor(RGB(0, 0, 0))
{
}


ImageKomastar::~ImageKomastar()
{
    if (m_pImageInfo)
    {
        SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hOldBit);
        DeleteObject(m_pImageInfo->hBit);
        DeleteDC(m_pImageInfo->hMemDC);

        if (m_szFileName)
        {
            delete m_szFileName;
        }
        delete m_pImageInfo;
    }
}

void ImageKomastar::Setup(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    m_pImageInfo = new IMAGE_INFO;
    m_pImageInfo->btLoadType = LOAD_EMPTY;
    m_pImageInfo->resID = 0;
    m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
    m_pImageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    m_pImageInfo->hOldBit = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
    m_pImageInfo->nWidth = width;
    m_pImageInfo->nHeight = height;

    ReleaseDC(g_hWnd, hdc);
}

void ImageKomastar::Setup(const char * FileName, int width, int height, bool isTrans, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    m_pImageInfo = new IMAGE_INFO;
    m_pImageInfo->btLoadType = LOAD_FILE;
    m_pImageInfo->resID = 0;
    m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
    m_pImageInfo->hBit = (HBITMAP)LoadImage(g_hInst, FileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    m_pImageInfo->hOldBit = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
    m_pImageInfo->nWidth = width;
    m_pImageInfo->nHeight = height;

    int len = (int)strlen(FileName);
    m_szFileName = new char[len + 1];
    strcpy_s(m_szFileName, len + 1, FileName);

    m_isTrans = isTrans;
    m_transColor = transColor;

    ReleaseDC(g_hWnd, hdc);
}

void ImageKomastar::SetupForAlphaBlend()
{
    // 알파블렌드 구조체 초기화 (기본 값을 바꿀 일이 없음)
    m_stBlendFunc.BlendOp = AC_SRC_OVER;
    m_stBlendFunc.BlendFlags = 0;
    m_stBlendFunc.AlphaFormat = 0;

    // DC 가져오기
    //HDC hdc = GetDC(g_hWnd);

    // 이미지 정보 새로 생성 및 초기화
    //m_pBlendImage = new IMAGE_INFO;
    //m_pBlendImage->btLoadType = LOAD_EMPTY;
    //m_pBlendImage->resID = 0;
    //m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
    //m_pBlendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, m_pImageInfo->nWidth, m_pImageInfo->nHeight);
    //m_pBlendImage->hOldBit = (HBITMAP)SelectObject(m_pBlendImage->hMemDC, m_pBlendImage->hBit);
    //m_pBlendImage->nWidth = W_WIDTH;
    //m_pBlendImage->nHeight = W_HEIGHT;

    // DC 해제
    //ReleaseDC(g_hWnd, hdc);
}

void ImageKomastar::Render(HDC hdc)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_transColor);
    }
    else
    {
        BitBlt(hdc, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_pImageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

void ImageKomastar::Render(HDC hdc, int destX, int destY)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc, destX, destY, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_transColor);
    }
    else
    {
        BitBlt(hdc, destX, destY, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_pImageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

void ImageKomastar::Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcW, int srcH)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc, destX, destY, srcW, srcH, m_pImageInfo->hMemDC, srcX, srcY, srcW, srcH, m_transColor);
    }
    else
    {
        BitBlt(hdc, destX, destY, srcW, srcH, m_pImageInfo->hMemDC, srcX, srcY, SRCCOPY);
    }
}

void ImageKomastar::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
    // 알파블렌드 처음 사용시 초기화
    if (!m_pBlendImage) SetupForAlphaBlend();

    // 알파값 초기화
    m_stBlendFunc.SourceConstantAlpha = alpha;

    if (m_isTrans)
    {
        //1. 출력해야 될 DC에 그려져 있는 내용을 블렌드이미지에 그려준다
        BitBlt(m_pBlendImage->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
            hdc, destX, destY, SRCCOPY);
        //2. 출력해야 될 이미지를 블렌드에 그려준다(마젠타 값을 없애준다)
        GdiTransparentBlt(m_pBlendImage->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
            m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_transColor);
        //3. 블렌드 DC를 출력해야 할 DC에 그린다
        GdiAlphaBlend(hdc, destX, destY, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
            m_pBlendImage->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_stBlendFunc);
    }
    else
    {
        // 알파블렌드 옵션 값을 사용해서 그린다.
        GdiAlphaBlend(hdc, destX, destY, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
            m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_stBlendFunc);
    }
}

void ImageKomastar::SetupForSprites(int MaxFrameX, int MaxFrameY, int SpritesWidth, int SpritesHeight, int SpritesDelay)
{
    m_currFrameX = 0;
    m_spritesInitDelay = SpritesDelay;
    m_spritesDelayCount = m_spritesInitDelay;
    m_maxFrameX = MaxFrameX;
    m_maxFrameY = MaxFrameY;
    m_spritesWidth = SpritesWidth;
    m_spritesHeight = SpritesHeight;
}

void ImageKomastar::SpritesRender(HDC hdc, RECT SpritesBox, BYTE alpha)
{
#ifdef _DEBUG
    Rectangle(g_hDC, SpritesBox.left, SpritesBox.top, SpritesBox.right, SpritesBox.bottom);
#endif
    POINT boxSize = { SpritesBox.right - SpritesBox.left, SpritesBox.bottom - SpritesBox.top };
    GdiTransparentBlt(hdc, SpritesBox.left, SpritesBox.top, 
                           boxSize.x, boxSize.y, 
                           m_pImageInfo->hMemDC, 
                           m_spritesWidth * m_currFrameX, 0, 
                           m_spritesWidth, m_spritesHeight, m_transColor);
}

void ImageKomastar::Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcW, int srcH, int alpha)
{
    GdiAlphaBlend(hdc, destX, destY, srcW, srcH, m_pImageInfo->hMemDC, srcX, srcY, srcW, srcH, m_stBlendFunc);
}

void ImageKomastar::Render(HDC hdc, int destX, int destY, int destW, int destH, int srcX, int srcY, int srcW, int srcH, int alpha)
{
    GdiAlphaBlend(hdc, destX, destY, destW, destH, m_pImageInfo->hMemDC, srcX, srcY, srcW, srcH, m_stBlendFunc);
}

void ImageKomastar::SetTransColor(bool isTrans, COLORREF transColor)
{
    m_isTrans = isTrans;
    m_transColor = transColor;
}

void ImageKomastar::Refresh()
{
    m_spritesDelayCount++;
    if (m_spritesDelayCount > m_spritesInitDelay)
    {
        m_spritesDelayCount = 0;
        if (m_maxFrameX > 0)
        {
            m_currFrameX++;
            if (m_currFrameX > m_maxFrameX - 1)
            {
                m_currFrameX = 0;
            }
        }
    }
}
