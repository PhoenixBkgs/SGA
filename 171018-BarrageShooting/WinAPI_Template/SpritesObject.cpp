#include "stdafx.h"
#include "SpritesObject.h"
#include "ImageObject.h"


SpritesObject::SpritesObject()
    : m_currFrameX(0)
    , m_currFrameY(0)
    , m_maxFrameX(1)
    , m_maxFrameY(1)
    , m_triggerPosX(-1)
    , m_frameDelay(0.0f)
    , m_frameDelayStep(1.0f)
    , m_delayCounter(0.0f)
    , m_spritesImg(NULL)
{
}


SpritesObject::~SpritesObject()
{
}

bool SpritesObject::IsTriggerFrame()
{
    if (m_triggerPosX == GetFrameX()) 
        return true; 
    else 
        return false;
}

void SpritesObject::NextFrame()
{
    m_delayCounter += m_frameDelayStep;
    if (m_delayCounter > m_frameDelay)
    {
        m_delayCounter = DELAY_RESET_VAL;
        m_currFrameX++;
    }
    ValidateFramePos();
}

void SpritesObject::SetupForSprites(int MaxFrameX, int MaxFrameY)
{
    m_spritesImg = new ImageObject;
    SetSpritesImg(m_imgBody);
    m_spritesImg->SetupForSprites(m_imgBody->GetWidth() / MaxFrameX, m_imgBody->GetHeight() / MaxFrameY, 0);
    m_maxFrameX = MaxFrameX - 1;
    m_maxFrameY = MaxFrameY - 1;
    UnitSize size = g_pDrawHelper->GetSizeFromRect(m_rtBody);
}

void SpritesObject::SetupDelay()
{
}

void SpritesObject::ValidateFramePos()
{
    m_currFrameX = m_currFrameX > m_maxFrameX ? 0 : m_currFrameX;
    m_currFrameY = m_currFrameY > m_maxFrameY ? 0 : m_currFrameY;
}


void SpritesObject::Render(HDC hdc)
{
    if (m_isVisible == true)
    {
        if (m_spritesImg != NULL)
        {
            m_spritesImg->SpritesRender(hdc, m_rtBody, m_currFrameX, m_currFrameY);
            NextFrame();
        }
#ifdef _DEBUG
        g_pDrawHelper->DrawBoxLine2D(m_rtBody, 5, _RGBA{ 0, 0, 0, 0 });         //  Draw body rect
        g_pDrawHelper->DrawBoxLine2D(m_rtHitBox, 2, _RGBA{ 0, 255, 0, 0 });     //  Draw hit box rect
#endif // _DEBUG
    }
}