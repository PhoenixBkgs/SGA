#include "stdafx.h"
#include "UserInterface.h"
#include "ImageKomastar.h"

UserInterface::UserInterface()
{
    m_alphaDelta = 0.5f;
    m_alpha = 0.0f;
}


UserInterface::~UserInterface()
{
    delete m_whBg;
}

void UserInterface::Render()
{
    switch (m_gameState)
    {
    case GAME_READY:
    {
        SplashScreen();
        break;
    }
    case GAME_PLAYING:
        break;
    case GAME_PAUSE:
        break;
    case GAME_CLEAR:
    {
        ClearScreen();
        break;
    }
    case GAME_OVER:
        break;
    }
}

void UserInterface::PaintBlack()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, BLACKNESS);
}

void UserInterface::PaintWhite()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
}

void UserInterface::SplashScreen()
{
    m_whBg->Render(g_hDC, 0, 0, 0, 0, W_WIDTH, W_HEIGHT, 255);

    string titleTxt = "FROZEN MARCH";
    RECT txtBox = { (W_WIDTH / 2) - (int)(titleTxt.size() * 50) - 100, W_HEIGHT / 2 - 50, W_WIDTH, W_HEIGHT / 2 + 50 };

    m_drawHelper.DrawTextBox(txtBox, titleTxt, _RGBA{ 155, 232, 254, 0 }, TEXT("Consolas"));

    string subtitleTxt = "Press Enter to Start";
    txtBox = { (int)(W_WIDTH * 0.5f) - (int)(subtitleTxt.size() * 15), (int)(W_HEIGHT * 0.77f) - 15, (int)(W_WIDTH * 0.5f) + ((int)subtitleTxt.size() * 15), (int)(W_HEIGHT * 0.77f) + 15 };
    if ((int)m_alpha % 128 < 64)
    {
        m_drawHelper.DrawTextBox(txtBox, subtitleTxt, _RGBA{ 5, 5, 5, 0 }, TEXT("Consolas"));
    }
    

    
    m_alpha += m_alphaDelta;
    if (m_alpha < 30.0f)
    {
        m_alpha = 30.0f;
        m_alphaDelta *= -1.0f;
    }
    else if (m_alpha > 200.0f)
    {
        m_alpha = 200.0f;
        m_alphaDelta *= -1.0f;
    }

#ifdef _DEBUG
    m_drawHelper.DrawLine2D(UnitPos{ W_WIDTH * 0.5f, 0.0f }, UnitPos{ W_WIDTH * 0.5f, W_HEIGHT }, 5, _RGBA{ 255, 255, 255, 255 });
    char infoMsg[100];
    sprintf_s(infoMsg, "ALPHA : %f", GetAlpha());
    TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}

void UserInterface::ClearScreen()
{

}

void UserInterface::SlideScreen(ImageKomastar * Image, double Acceleration, int Divide, bool IsStartLeft, double Delay)
{
    if (Image != NULL)
    {
        double renderPosX = m_slidePosX;
        double renderPosY = (W_HEIGHT - Image->GetHeight()) * 0.5f;

        if (IsStartLeft == false)
        {
            renderPosX = -renderPosX;
        }

        for (int divCount = 0; divCount < Divide; divCount++)
        {
            double pieceHeight = Image->GetHeight() / Divide;
            Image->Render(g_hDC
                        , -(int)renderPosX, (int)renderPosY
                        , 0, (int)(pieceHeight * divCount)
                        , Image->GetWidth(), (int)pieceHeight
                        , 255);

            renderPosX = -renderPosX;
            renderPosY += pieceHeight;
        }

        if (m_slidePosX > m_slideSpeed)
        {
            
        }
        else
        {
            m_slideDelayCount += 1.0f;
            if (m_slideDelayCount > Delay)
            {
                m_slidePosX -= m_slideSpeed;
            }
            else
            {
                m_slidePosX = 0.0f;
                m_slideSpeed = 1.0f;
            }
        }

        m_slidePosX -= m_slideSpeed;
        m_slideSpeed += Acceleration;
    }
#ifdef _DEBUG
    char infoMsg[100];
    sprintf_s(infoMsg, "PosX : %f", m_slidePosX);
    TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}

void UserInterface::ResetSlide()
{
    m_slidePosX = W_WIDTH;
    m_slideSpeed = 0.0f;
    m_slideDelayCount = 0.0f;
    m_slideMagnifier = 1.0f;
}
