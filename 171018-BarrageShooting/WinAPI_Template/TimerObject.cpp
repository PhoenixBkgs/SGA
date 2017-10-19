#include "stdafx.h"
#include "TimerObject.h"

TimerObject::TimerObject()
    : m_maxCount(1)
    , m_curCount(0)
    , m_tick(1)
{
}

TimerObject::~TimerObject()
{
}

void TimerObject::Setup(int MaxCount)
{
    Setup(MaxCount, 1);
}

void TimerObject::Setup(int MaxCount, int Tick)
{
    m_maxCount = MaxCount;
    m_tick = Tick;
}

void TimerObject::Tick()
{
    m_curCount += m_tick;
    if (m_curCount > m_maxCount)
        m_curCount = 0;
}
