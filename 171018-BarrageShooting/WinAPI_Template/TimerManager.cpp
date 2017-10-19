#include "stdafx.h"
#include "TimerManager.h"

TimerObject * TimerManager::AddTimer(string Key, int MaxCount)
{
    return AddTimer(Key, MaxCount, 1);
}

TimerObject * TimerManager::AddTimer(string Key, int MaxCount, int Tick)
{
    TimerObject* timerObj = FindTimer(Key);
    if (timerObj == NULL)
    {
        timerObj = new TimerObject;
        timerObj->Setup(MaxCount, Tick);
        m_mapTimer.insert(make_pair(Key, timerObj));
    }
    return timerObj;
}

TimerObject* TimerManager::AddTimer(string Key, TimerObject* TimerObj)
{
    TimerObject* timerObj = FindTimer(Key);
    if (timerObj == NULL)
    {
        m_mapTimer.insert(make_pair(Key, TimerObj));
    }
    return timerObj;
}

TimerObject* TimerManager::FindTimer(string Key)
{
    m_mapIter = m_mapTimer.find(Key);
    if (m_mapIter != m_mapTimer.end())
        return m_mapIter->second;
    else
        return NULL;
}

void TimerManager::TickTimer(string Key)
{
    m_timerObject = FindTimer(Key);
    m_timerObject->Tick();
    m_timerObject = NULL;
}

void TimerManager::DeleteTimerByKey(string Key)
{
}

void TimerManager::DeleteTimerAll()
{
}
