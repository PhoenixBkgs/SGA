#include "stdafx.h"
#include "ImageObject.h"
#include "DrawHelper.h"
#include "GeometryHelper.h"

ImageObject::ImageObject()
    :m_pImageInfo(NULL)
    ,m_szFileName(NULL)
    ,m_isTrans(true)
    ,m_transColor(RGB(255, 0, 255))
    ,m_drawHelper(NULL)
    ,m_pBlendImage(NULL)
{
}

ImageObject::~ImageObject()
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

void ImageObject::Setup(int width, int height)
{
    Setup(NULL, width, height);
}

void ImageObject::Setup(const char * FileName, int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    m_pImageInfo = new IMAGE_INFO;
    m_pImageInfo->btLoadType = LOAD_FILE;
    m_pImageInfo->resID = 0;
    m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
    if (FileName == NULL)
    {
        m_pImageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    }
    else
    {
        m_pImageInfo->hBit = (HBITMAP)LoadImage(g_hInst, FileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
        int len = (int)strlen(FileName);
        m_szFileName = new char[len + 1];
        strcpy_s(m_szFileName, len + 1, FileName);
    }
    m_pImageInfo->hOldBit = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
    m_pImageInfo->nWidth = width;
    m_pImageInfo->nHeight = height;

    m_isTrans = true;
    m_transColor = RGB(255, 0, 255);

    m_stBlendFunc.BlendOp = AC_SRC_OVER;
    m_stBlendFunc.BlendFlags = 0;
    m_stBlendFunc.AlphaFormat = 0;

    SetupForAlphaBlend();

    ReleaseDC(g_hWnd, hdc);
}

void ImageObject::SetupForAlphaBlend()
{
    // 알파블렌드 구조체 초기화 (기본 값을 바꿀 일이 없음)
    // DC 가져오기
    HDC hdc = GetDC(g_hWnd);

    // 이미지 정보 새로 생성 및 초기화
    m_pBlendImage = new IMAGE_INFO;
    m_pBlendImage->btLoadType = LOAD_EMPTY;
    m_pBlendImage->resID = 0;
    m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
    m_pBlendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, m_pImageInfo->nWidth, m_pImageInfo->nHeight);
    m_pBlendImage->hOldBit = (HBITMAP)SelectObject(m_pBlendImage->hMemDC, m_pBlendImage->hBit);
    m_pBlendImage->nWidth = W_WIDTH;
    m_pBlendImage->nHeight = W_HEIGHT;

    // DC 해제
    ReleaseDC(g_hWnd, hdc);
}

void ImageObject::Render(HDC hdc, UnitPos DestPos, UnitSize DestSize, int FrameX, int FrameY, double Ratio)
{
    GdiTransparentBlt(hdc
        , (int)(DestPos.x - m_spritesWidth * 0.5f), (int)(DestPos.y - m_spritesHeight * 0.5f)
        , (int)(m_spritesWidth * Ratio), m_spritesHeight
        , m_pImageInfo->hMemDC
        , m_spritesWidth * FrameX, m_spritesHeight * FrameY
        , (int)(m_spritesWidth * Ratio), m_spritesHeight
        , m_transColor);
}

void ImageObject::Render(HDC hdc)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc
                        , 0, 0
                        , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                        , m_pImageInfo->hMemDC
                        , 0, 0
                        , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                        , m_transColor);
    }
    else
    {
        BitBlt(hdc
            , 0, 0
            , m_pImageInfo->nWidth, m_pImageInfo->nHeight
            , m_pImageInfo->hMemDC
            , 0, 0
            , SRCCOPY);
    }
}

void ImageObject::Render(HDC hdc, UnitPos Pos)
{
    GdiTransparentBlt(hdc
                    , (int)(Pos.x - GetWidth() * 0.5f), (int)(Pos.y - GetHeight() * 0.5f)
                    , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                    , m_pImageInfo->hMemDC
                    , 0, 0
                    , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                    , m_transColor);
}

void ImageObject::Render(HDC hdc, int destX, int destY)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc
                        , destX, destY
                        , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                        , m_pImageInfo->hMemDC
                        , 0, 0
                        , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                        , m_transColor);
    }
    else
    {
        BitBlt(hdc
            , destX, destY
            , m_pImageInfo->nWidth, m_pImageInfo->nHeight
            , m_pImageInfo->hMemDC
            , 0, 0
            , SRCCOPY);
    }
}

void ImageObject::Render(HDC hdc, int destX, int destY, int destW, int destH)
{
    GdiTransparentBlt(hdc
                    , destX, destY
                    , destW, destH
                    , m_pImageInfo->hMemDC
                    , 0, 0
                    , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                    , m_transColor);
}

void ImageObject::Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcW, int srcH)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc
                        , destX, destY
                        , srcW, srcH
                        , m_pImageInfo->hMemDC
                        , srcX, srcY
                        , srcW, srcH
                        , m_transColor);
    }
    else
    {
        BitBlt(hdc
            , destX, destY
            , srcW, srcH
            , m_pImageInfo->hMemDC
            , srcX, srcY
            , SRCCOPY);
    }
}

void ImageObject::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
    // 알파블렌드 처음 사용시 초기화
    if (!m_pBlendImage)
    {
        SetupForAlphaBlend();
    }

    // 알파값 초기화
    m_stBlendFunc.SourceConstantAlpha = alpha;

    if (m_isTrans)
    {
        //1. 출력해야 될 DC에 그려져 있는 내용을 블렌드이미지에 그려준다
        BitBlt(m_pBlendImage->hMemDC
            , 0, 0
            , m_pImageInfo->nWidth, m_pImageInfo->nHeight
            , hdc
            , destX, destY
            , SRCCOPY);
        //2. 출력해야 될 이미지를 블렌드에 그려준다(마젠타 값을 없애준다)
        GdiTransparentBlt(m_pBlendImage->hMemDC
                        , 0, 0
                        , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                        , m_pImageInfo->hMemDC
                        , 0, 0
                        , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                        , m_transColor);
        //3. 블렌드 DC를 출력해야 할 DC에 그린다
        
        GdiAlphaBlend(hdc
                    , destX, destY
                    , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                    , m_pBlendImage->hMemDC
                    , 0, 0
                    , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                    , m_stBlendFunc);
    }
    else
    {
        // 알파블렌드 옵션 값을 사용해서 그린다.
        GdiAlphaBlend(hdc
                    , destX, destY
                    , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                    , m_pImageInfo->hMemDC
                    , 0, 0
                    , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                    , m_stBlendFunc);
    }
}

void ImageObject::SetupForSprites(int SpritesWidth, int SpritesHeight, int SpritesDelay)
{
    m_spritesWidth = SpritesWidth;
    m_spritesHeight = SpritesHeight;
}

void ImageObject::SpritesRender(HDC hdc, RECT SpritesBox, BYTE alpha)
{
#ifdef _DEBUG
    if (m_drawHelper != NULL)
    {
        m_drawHelper->DrawBoxLine2D(SpritesBox, 5, _RGBA{ 0, 255, 0, 0 });
    }
#endif
    POINT boxSize = { SpritesBox.right - SpritesBox.left, SpritesBox.bottom - SpritesBox.top };
    GdiTransparentBlt(hdc
                    , SpritesBox.left, SpritesBox.top
                    , boxSize.x, boxSize.y
                    , m_pImageInfo->hMemDC
                    , m_spritesWidth * 0, m_spritesHeight * 0
                    , m_spritesWidth, m_spritesHeight
                    , m_transColor);
}

void ImageObject::SpritesRender(HDC hdc, RECT SpritesBox, int FrameX, int FrameY)
{
    POINT boxSize = { SpritesBox.right - SpritesBox.left, SpritesBox.bottom - SpritesBox.top };
    GdiTransparentBlt(hdc
                         , SpritesBox.left, SpritesBox.top
                         , boxSize.x, boxSize.y
                         , m_pImageInfo->hMemDC
                         , m_spritesWidth * FrameX, m_spritesHeight * FrameY
                         , m_spritesWidth, m_spritesHeight
                         , m_transColor);
}

void ImageObject::SpritesRender(HDC hdc, RECT SpritesBox, int FrameX, int FrameY, double Alpha)
{
    m_stBlendFunc.SourceConstantAlpha = (BYTE)Alpha;
    POINT boxSize = { SpritesBox.right - SpritesBox.left, SpritesBox.bottom - SpritesBox.top };
    BitBlt(m_pBlendImage->hMemDC
        , 0, 0
        , m_pImageInfo->nWidth, m_pImageInfo->nHeight
        , hdc
        , SpritesBox.left, SpritesBox.top
        , SRCCOPY);

    GdiTransparentBlt(m_pBlendImage->hMemDC
        , 0, 0
        , m_spritesWidth, m_spritesHeight
        , m_pImageInfo->hMemDC
        , m_spritesWidth * FrameX, m_spritesHeight * FrameY
        , m_spritesWidth, m_spritesHeight
        , m_transColor);

    GdiAlphaBlend(hdc
        , SpritesBox.left, SpritesBox.top
        , boxSize.x, boxSize.y
        , m_pBlendImage->hMemDC
        , 0, 0
        , m_spritesWidth, m_spritesHeight
        , m_stBlendFunc);
}


void ImageObject::SpritesRender(HDC hdc, UnitPos Pos, BYTE alpha)
{
    BitBlt(m_pBlendImage->hMemDC
                    , 0, 0
                    , m_spritesWidth, m_spritesWidth
                    , hdc
                    , (int)Pos.x - m_spritesWidth, (int)Pos.y - m_spritesHeight
                    , SRCCOPY);

    GdiTransparentBlt(m_pBlendImage->hMemDC
                    , 0, 0
                    , m_spritesWidth, m_spritesHeight
                    , m_pImageInfo->hMemDC
                    , 0, 0
                    , m_spritesWidth, m_spritesHeight
                    , m_transColor);
    
    GdiAlphaBlend(hdc
                    , (int)Pos.x - m_spritesWidth, (int)Pos.y - m_spritesHeight
                    , m_spritesWidth, m_spritesWidth
                    , m_pBlendImage->hMemDC
                    , 0, 0
                    , m_spritesWidth, m_spritesWidth
                    , m_stBlendFunc);
}

void ImageObject::SpritesRender(HDC hdc, UnitPos DestPos, UnitSize DestSize, int FrameX, int FrameY)
{
    GdiTransparentBlt(hdc
        , (int)(DestPos.x - DestSize.w * 0.5f), (int)(DestPos.y - DestSize.h * 0.5f)
        , DestSize.w, DestSize.h
        , m_pImageInfo->hMemDC
        , m_spritesWidth * FrameX, m_spritesHeight * FrameY
        , m_spritesWidth, m_spritesHeight
        , m_transColor);
}

void ImageObject::SpritesRender(HDC hdc, UnitPos RightEndPos, UnitSize EachSize, int Number)
{
    int tempScore = Number;
    UnitPos renderPos = RightEndPos;

    while (tempScore != 0)
    {
        int printNumber = tempScore % 10;

        //  NUMBER RENDERER
        SpritesRender(hdc, renderPos, EachSize, printNumber, 0);
        renderPos.x -= (double)EachSize.w;
        tempScore = tempScore / 10;
    }
}


void ImageObject::Render(HDC hdc, UnitPos KeyPos, double Angle)
{
    UnitPos pt1 = UnitPos{ (KeyPos.x - m_pImageInfo->nWidth * 0.5f), (KeyPos.y - m_pImageInfo->nHeight * 0.5f) };
    UnitPos pt2 = UnitPos{ (KeyPos.x + m_pImageInfo->nWidth * 0.5f), (KeyPos.y - m_pImageInfo->nHeight * 0.5f) };
    UnitPos pt3 = UnitPos{ (KeyPos.x - m_pImageInfo->nWidth * 0.5f), (KeyPos.y + m_pImageInfo->nHeight * 0.5f) };
    m_geoHelper = new GeometryHelper;

    pt1 = m_geoHelper->GetRotateCoord(KeyPos, pt1, Angle);
    pt2 = m_geoHelper->GetRotateCoord(KeyPos, pt2, Angle);
    pt3 = m_geoHelper->GetRotateCoord(KeyPos, pt3, Angle);

    POINT Pt[3] = {
          POINT{ (LONG)pt1.x, (LONG)pt1.y }
        , POINT{ (LONG)pt2.x, (LONG)pt2.y }
        , POINT{ (LONG)pt3.x, (LONG)pt3.y }
    };

    BitBlt(m_pBlendImage->hMemDC
                    , 0, 0
                    , W_WIDTH, W_HEIGHT
                    , hdc
                    , 0, 0
                    , SRCCOPY);
    
    PlgBlt(m_pBlendImage->hMemDC, Pt, m_pImageInfo->hMemDC
                    , 0, 0
                    , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                    , NULL
                    , 0, 0);
    
    GdiTransparentBlt(hdc
                    , 0, 0
                    , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                    , m_pBlendImage->hMemDC
                    , 0, 0
                    , m_pImageInfo->nWidth, m_pImageInfo->nHeight
                    , m_transColor);
}

void ImageObject::Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcW, int srcH, int alpha)
{
    Render(hdc
        , destX, destY
        , m_pImageInfo->nWidth, m_pImageInfo->nHeight
        , srcX, srcY
        , srcW, srcH
        , alpha);
}

void ImageObject::Render(HDC hdc, int destX, int destY, int destW, int destH, int srcX, int srcY, int srcW, int srcH, int alpha)
{
    m_stBlendFunc.SourceConstantAlpha = alpha;
    GdiAlphaBlend(hdc
                , destX, destY
                , destW, destH
                , m_pImageInfo->hMemDC
                , srcX, srcY
                , srcW, srcH
                , m_stBlendFunc);
}

void ImageObject::SetTransColor(bool isTrans, COLORREF transColor)
{
    m_isTrans = isTrans;
    m_transColor = transColor;
}