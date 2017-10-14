#pragma once
#include "EnumState.h"
#include "Draw2DKomastar.h"

#define SPLASH_MAX_COUNT    (255 * 10)

class ImageKomastar;
class UserInterface
{
private:
    Draw2DKomastar  m_drawHelper;
    E_GAME_STATE    m_gameState;
    double          m_alpha;
    double          m_alphaDelta;
    ImageKomastar*  m_whBg;
    ImageKomastar*  m_SlideImg;

    double          m_slidePosX;
    double          m_slideSpeed;
    double          m_slideDelayCount;
    double          m_slideMagnifier;
public:
    UserInterface();
    ~UserInterface();

    void SetGameState(E_GAME_STATE State) { m_gameState = State; }
    void SetImg(ImageKomastar* Image) { m_whBg = Image; }
    double GetAlpha() { return m_alpha; }
    void Render();

    void PaintBlack();
    void PaintWhite();

    void SplashScreen();
    void ClearScreen();

    void SlideScreen(ImageKomastar* Image, double Acceleration, int Divide, bool IsStartLeft, double Delay);
    void SetSlideSpeed(double Speed) { m_slideSpeed = Speed; }
    double GetSlideSpeed() { return m_slideSpeed; }
    void ResetSlide();
};

