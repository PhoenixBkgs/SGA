#pragma once
class TimerObject
{
private:
    int m_maxCount;
    int m_curCount;
    int m_tick;

public:
    TimerObject();
    ~TimerObject();

    void Setup(int MaxCount);
    void Setup(int MaxCount, int Tick);
    void Tick();
};