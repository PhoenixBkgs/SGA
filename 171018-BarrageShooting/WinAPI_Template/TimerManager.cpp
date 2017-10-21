#include "stdafx.h"
#include "TimerManager.h"

bool TimerManager::AddSimpleTimer(string Key)
{
    m_mapSimpleIter = m_mapSimpleTimer.find(Key);
    if (m_mapSimpleIter != m_mapSimpleTimer.end())
    {
        return false;
    }
    else
    {
        m_mapSimpleTimer.insert(make_pair(Key, 0));
        return true;
    }
}

bool TimerManager::AddOnOffTimer(string Key, UnitPos ShiftPos, float Tick, float Multiplier)
{
    m_mapOnOffIter = m_mapOnOffTimer.find(Key);
    if (m_mapOnOffIter != m_mapOnOffTimer.end())
    {
        return false;
    }
    else
    {
        m_mapOnOffTimer.insert(make_pair(Key, (0.0f + (float)ShiftPos.x)));
        m_mapOnOffTick.insert(make_pair(Key, Tick));
        m_mapOnOffMltply.insert(make_pair(Key, Multiplier));
        m_mapOnOffShiftY.insert(make_pair(Key, (float)ShiftPos.y));
        return true;
    }
}

int TimerManager::FindSimpleTick(string Key)
{
    m_mapSimpleIter = m_mapSimpleTimer.find(Key);
    if (m_mapSimpleIter != m_mapSimpleTimer.end())
    {
        return m_mapSimpleIter->second;
    }
    else
    {
        return -1;  //   -1 find fail
    }
}

float TimerManager::FindOnOffTick(string Key)
{
    m_mapOnOffIter = m_mapOnOffTimer.find(Key);
    if (m_mapOnOffIter != m_mapOnOffTimer.end())
    {
        //  found
        float angle = m_mapOnOffIter->second;
        m_mapOnOffIter->second += m_mapOnOffTick.find(Key)->second;
        if (m_mapOnOffIter->second > 360.0f)
            m_mapOnOffIter->second = 0.0f;
        float result = sinf(angle);
        return (result * m_mapOnOffMltply.find(Key)->second ) + m_mapOnOffShiftY.find(Key)->second;
    }
    else
    {
        return 0.0f;
    }
}

bool TimerManager::SetSimpleTick(string Key, int Tick)
{
    m_mapSimpleIter = m_mapSimpleTimer.find(Key);
    if (m_mapSimpleIter != m_mapSimpleTimer.end())
    {
        m_mapSimpleIter->second = Tick;
        return true;
    }
    else
    {
        return false;
    }
}

int TimerManager::TickSimpleTimer(string Key)
{
    if (SetSimpleTick(Key, FindSimpleTick(Key) + 1))
    {
        return FindSimpleTick(Key);
    }
    else
    {
        return -1;
    }
}

bool TimerManager::ResetSimpleTimer(string Key)
{
    m_mapSimpleIter = m_mapSimpleTimer.find(Key);
    if (m_mapSimpleIter != m_mapSimpleTimer.end())
    {
        m_mapSimpleIter->second = 0;
        return true;
    }
    else
    {
        return false;
    }
}

bool TimerManager::TickOnOffTimer(string Key)
{
    float tick = FindOnOffTick(Key);

    //  -1.0f ~ tick ~ +1.0f
    if (tick >= m_mapOnOffShiftY.find(Key)->second)
        return true;
    else
        return false;
}

bool TimerManager::DeleteSimpleTimerByKey(string Key)
{
    m_mapSimpleIter = m_mapSimpleTimer.find(Key);
    if (m_mapSimpleIter != m_mapSimpleTimer.end())
    {
        m_mapSimpleTimer.erase(m_mapSimpleIter);
        return true;
    }
    else
    {
        return false;
    }
}

void TimerManager::DeleteTimerAll()
{
    m_mapSimpleIter = m_mapSimpleTimer.begin();
    while (m_mapSimpleIter != m_mapSimpleTimer.end())
    {
        m_mapSimpleIter = m_mapSimpleTimer.erase(m_mapSimpleIter);
    }
}
