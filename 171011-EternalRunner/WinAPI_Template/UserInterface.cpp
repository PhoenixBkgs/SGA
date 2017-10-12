#include "stdafx.h"
#include "UserInterface.h"
#include "ImageKomastar.h"

UserInterface::UserInterface()
{
    m_whBg = new ImageKomastar;
    m_whBg->Setup("images/whiteBg.bmp", 1920, 1080);
    m_whBg->SetupForAlphaBlend();
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

void UserInterface::SplashScreen()
{
    string titleTxt = "RUN AWAY KOMASTAR";
    RECT txtBox = { (W_WIDTH / 2) - ((int)titleTxt.size() * 50), W_HEIGHT / 2 - 50, W_WIDTH, W_HEIGHT / 2 + 50 };
    m_drawHelper.DrawTextBox(txtBox, titleTxt, _RGBA{ 100, 100, 100, 100 }, TEXT("Consolas"));

    string subtitleTxt = "Press Enter to Start";
    txtBox = { (int)(W_WIDTH * 0.5f) - ((int)subtitleTxt.size() * 15), (int)(W_HEIGHT * 0.77f) - 15, (int)(W_WIDTH * 0.5f) + ((int)subtitleTxt.size() * 15), (int)(W_HEIGHT * 0.77f) + 15 };
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

    m_whBg->Render(g_hDC, 0, 0, 0, 0, W_WIDTH, W_HEIGHT, (int)m_alpha);
#ifdef _DEBUG
    char infoMsg[100];
    sprintf_s(infoMsg, "ALPHA : %f", GetAlpha());
    TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG

}

void UserInterface::ClearScreen()
{

}
