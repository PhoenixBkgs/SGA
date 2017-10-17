#pragma once
#include "GameObject.h"

#define PLAYER_WIDTH    150
#define PLAYER_HEIGHT   150
#define POWER_STEP  1.0f

class Arrow;
class Player : public GameObject
{
private:
    //  MUTUAL REF
    Arrow*              m_pArrow;
    RECT                m_rtGauge;
    RECT                m_rtGaugeFill;
    double              m_dPowerGauge;
    double              m_dPowerStep;
    HBRUSH*             m_brushGauge;
    bool                m_isPullingTrigger;
    int                 m_nScore;
public:
    Player();
    ~Player();

    void Setup();
    void Update();

#pragma region SET
    void SetPowerGauge(double Gauge) { m_dPowerGauge; }
    void SetArrow(Arrow* Arrow) { m_pArrow = Arrow; }
    void SumScore(int Score) { m_nScore += Score; }
#pragma endregion

#pragma region GET
    double  GetPowerGauge() { return m_dPowerGauge; }
    double  GetPowerStep() { return m_dPowerStep; }
    bool    GetIsPulling() { return m_isPullingTrigger; }
    int     GetScore() { return m_nScore; }
#pragma endregion

    void PullTrigger();
    void Shoot();
    void GaugeRender();
};

