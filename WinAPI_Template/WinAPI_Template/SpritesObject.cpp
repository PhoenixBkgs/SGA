#include "stdafx.h"
#include "SpritesObject.h"
#include "GameObject.h"
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
    m_spritesImg->SpritesRender(hdc, m_gameObj->GetBodyRect(), m_currFrameX, m_currFrameY);
}
