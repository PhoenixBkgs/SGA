#pragma once
#include "ShootingTarget.h"

class ShootingGallery
{
//  VARS
private:
    int m_smallTargetCount;
    int m_mediumTargetCount;
    int m_largeTargetCount;

public:
    vector<ShootingTarget> m_vecTarget;

//  FUNCS
private:

public:
    ShootingGallery();
    ~ShootingGallery();

    void SetShootingGallery(int STargetCount, int MTargetCount, int LTargetCount) {
        m_smallTargetCount = STargetCount;
        m_mediumTargetCount = MTargetCount;
        m_largeTargetCount = LTargetCount;
    }
    int GetEntireTargetCount() {
        return m_smallTargetCount + m_mediumTargetCount + m_largeTargetCount;
    }

    void SetupTargets();
};

