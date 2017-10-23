#pragma once
#include "SingletonBase.h"

class TimerManager : public SingletonBase<TimerManager>
{
    //  VARS
private:
    map<string, int>                        m_mapSimpleTimer;
    map<string, int>::iterator              m_mapSimpleIter;

    map<string, float>                      m_mapOnOffTimer;
    map<string, float>::iterator            m_mapOnOffIter;

    map<string, float>                      m_mapOnOffShiftY;
    map<string, float>                      m_mapOnOffTick;
    map<string, float>                      m_mapOnOffMltply;
public:

    //  FUNCS
private:
public:
#pragma region CRUD
    //  CREATE
    bool    AddSimpleTimer(string Key);
    bool    AddOnOffTimer(string Key, UnitPos ShiftPos = { 0.0f, 0.0f }, float Tick = 0.1f, float Multiplier = 1.0f);
    //  READ
    int     FindSimpleTick(string Key);
    float   FindOnOffTick(string Key);
    //  UPDATE
    bool    SetSimpleTick(string Key, int Tick);
    int     TickSimpleTimer(string Key);
    bool    ResetSimpleTimer(string Key);
    bool    TickOnOffTimer(string Key);
    //  DELETE
    bool    DeleteSimpleTimerByKey(string Key);
    void    DeleteTimerAll();
#pragma endregion
};