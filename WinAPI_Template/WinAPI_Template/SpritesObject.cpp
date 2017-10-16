#include "stdafx.h"
#include "SpritesObject.h"
#include "GameObject.h"
#include "ImageObject.h"


SpritesObject::SpritesObject()
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
    m_currFrameX++;
    ValidateFramePos();
}

void SpritesObject::ValidateFramePos()
{
    if (m_currFrameX > m_maxFrameX)
    {
        m_currFrameX = 0;
    }

    if (m_currFrameY > m_maxFrameY)
    {
        m_currFrameY = 0;
    }
}

void SpritesObject::Render(HDC hdc)
{
    m_spritesImg->SpritesRender(hdc, m_gameObj->GetBodyRect(), m_currFrameX, m_currFrameY);
}
