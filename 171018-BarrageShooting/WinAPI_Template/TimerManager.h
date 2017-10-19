#pragma once
#include "SingletonBase.h"
#include "TimerObject.h"

class TimerManager : public SingletonBase<TimerManager>
{
    //  VARS
private:
    map<string, TimerObject*>            m_mapTimer;
    map<string, TimerObject*>::iterator  m_mapIter;
    TimerObject*    m_timerObject;
public:
    //  FUNCS
private:
public:
#pragma region CRUD
    //  CREATE
    TimerObject*    AddTimer(string Key, int MaxCount);
    TimerObject*    AddTimer(string Key, int MaxCount, int Tick);
    TimerObject*    AddTimer(string Key, TimerObject* TimerObj);
    //  READ
    TimerObject*    FindTimer(string Key);
    //  UPDATE
    void    TickTimer(string Key);
    template <class T>
    void    TickTimer(string Key, T Tick);
    //  DELETE
    void    DeleteTimerByKey(string Key);
    void    DeleteTimerAll();
    
#pragma endregion

};

template<class T>
inline void TimerManager::TickTimer(string Key, T Tick)
{
}
