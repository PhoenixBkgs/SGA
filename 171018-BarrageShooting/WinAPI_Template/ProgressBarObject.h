#pragma once
#include "GameObject.h"
#include "SpritesObject.h"

class ProgressBarObject : public GameObject
{
private:
    bool                m_bIsSetup;
    SpritesObject*      m_spritesBack;      //  Background img
    SpritesObject*      m_spritesFront;     //  Foreground img
    double              m_dGaugeRatio;
public:
    ProgressBarObject();
    ~ProgressBarObject();

#pragma region GET
    double  GetGaugeRatio() { return m_dGaugeRatio; }
    SpritesObject*  GetSpritesBack() { return m_spritesBack; }
    SpritesObject*  GetSpritesFront() { return m_spritesFront; }
#pragma endregion
#pragma region SET
    void    SetGaugeRatio(double Ratio) { m_dGaugeRatio = Ratio; }
    void    SetIsSetup() { m_bIsSetup = true; }
    void    SetSpritesBack(ImageObject* Image);
    void    SetSpritesFront(ImageObject* Image);
#pragma endregion

#pragma region RENDER
    void    Render(HDC hdc);
#pragma endregion
    void    SetupSprites();
};