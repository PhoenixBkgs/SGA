#pragma once
#include "EnumState.h"
#include "Draw2DKomastar.h"
#include "Geometry2DKomastar.h"

#define SPLASH_MAX_COUNT    (255 * 10)

class ImageKomastar;
class UserInterface
{
private:
    Draw2DKomastar  m_drawHelper;
    Geometry2DKomastar m_geoHelper;
    E_GAME_STATE    m_gameState;
    double          m_alpha;
    double          m_alphaDelta;
    double          m_deltaAngle;

    ImageKomastar*  m_hotsBladeImg;
    ImageKomastar*  m_hotsBg;
    ImageKomastar*  m_slideImg;

    double          m_slidePosX;
    double          m_slideSpeed;
    double          m_slideDelayCount;
    double          m_slideMagnifier;

    UnitPos m_pos;
    UnitPos m_pt1;
    UnitPos m_pt2;
    UnitPos m_pt3;
public:
    UserInterface();
    ~UserInterface();

    void SetGameState(E_GAME_STATE State) { m_gameState = State; }
    void SetBgImg(ImageKomastar* Image) { m_hotsBg = Image; }
    void SetBladeImg(ImageKomastar* Image) { m_hotsBladeImg = Image; }
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

