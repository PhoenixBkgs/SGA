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

int TimerManager::FindTick(string Key)
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

bool TimerManager::SetTick(string Key, int Tick)
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
    if (SetTick(Key, FindTick(Key) + 1))
    {
        return FindTick(Key);
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

bool TimerManager::DeleteTimerByKey(string Key)
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
