#include "..\SGA\WinAPI_Template\WinAPI_Template\stdafx.h"
#include "SpritesObject.h"


SpritesObject::SpritesObject()
    : m_currFrameX(0)
    , m_currFrameY(0)
    , m_maxFrameX(0)
    , m_maxFrameY(0)
{
}


SpritesObject::~SpritesObject()
{
}

void SpritesObject::NextFrame()
{
    m_currFrameX++;
    if (m_currFrameX > m_maxFrameX)
    {
        m_currFrameX = 0;
    }
}
