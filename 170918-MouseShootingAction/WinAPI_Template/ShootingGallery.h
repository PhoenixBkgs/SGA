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

//  FUNCS
private:

public:
    ShootingGallery();
    ~ShootingGallery();

    void CreateShootingGallery(int STargetCount, int MTargetCount, int LTargetCount);
};

