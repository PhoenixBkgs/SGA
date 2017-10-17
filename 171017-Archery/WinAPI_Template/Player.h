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
    double              m_dPowerGauge;
    double              m_dPowerStep;

public:
    Player();
    ~Player();

    void Setup();
    void Update();

#pragma region SET
    void SumPowerGauge() { m_dPowerGauge += m_dPowerStep; }
    void SumPowerGauge(double Gauge) { m_dPowerGauge += Gauge; }
    void SetArrow(Arrow* Arrow) { m_pArrow = Arrow; }
#pragma endregion

#pragma region GET
    double  GetPowerGauge() { return m_dPowerGauge; }
    double  GetPowerStep() { return m_dPowerStep; }
#pragma endregion


    void Shoot();
};

