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

public:
    UserInterface();
    ~UserInterface();

    void SetGameState(E_GAME_STATE State) { m_gameState = State; }
    void SetImg(ImageKomastar* Image) { m_whBg = Image; }
    double GetAlpha() { return m_alpha; }
    void Render();
    void SplashScreen();
    void ClearScreen();
};

