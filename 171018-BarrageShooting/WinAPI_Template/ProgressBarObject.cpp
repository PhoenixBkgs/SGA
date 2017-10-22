#include "stdafx.h"
#include "ProgressBarObject.h"


ProgressBarObject::ProgressBarObject()
    : m_bIsSetup(false)
{
}

ProgressBarObject::~ProgressBarObject()
{
}

void ProgressBarObject::SetSpritesBack(ImageObject * Image)
{
    m_spritesBack = new SpritesObject;
    m_spritesBack->SetBodyImg(Image);
}

void ProgressBarObject::SetSpritesFront(ImageObject * Image)
{
    m_spritesFront = new SpritesObject;
    m_spritesFront->SetBodyImg(Image);
    m_spritesFront->SetFrameDelay(3.0f);
}

void ProgressBarObject::Render(HDC hdc)
{
    if (m_bIsSetup)
    {
        m_spritesBack->SetBodyRect(m_rtBody);
        m_spritesBack->GetSpritesImg()->Render(g_hDC, m_dPos, m_nSize, 0, 1, 1.0f);
        m_spritesFront->SetBodyRect(m_rtBody);
        m_spritesFront->GetSpritesImg()->Render(g_hDC, m_dPos, m_nSize, 0, m_spritesFront->GetFrameY(), m_dGaugeRatio);
        m_spritesFront->NextFrameY();
        m_spritesBack->GetSpritesImg()->Render(g_hDC, m_dPos, m_nSize, 0, 0, 1.0f);
    }
}

void ProgressBarObject::SetupSprites()
{
    m_spritesBack->SetBodyRect(m_rtBody);
    m_spritesBack->SetupForSprites(1, 2);
    m_spritesFront->SetBodyRect(m_rtBody);
    m_spritesFront->SetupForSprites(1, 8);
}
