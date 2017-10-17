#include "stdafx.h"
#include "Wind.h"


Wind::Wind()
{
}


Wind::~Wind()
{
}

void Wind::Setup()
{
    double dWindSpeedX = ((rand() % 101) - 50) * 0.01f;
    double dWindSpeedY = ((rand() % 101) - 50) * 0.01f;
    double dWindSpeedZ = ((rand() % 101) - 50) * 0.01f;
    m_dSpeed3D.x = dWindSpeedX;
    m_dSpeed3D.y = dWindSpeedY;
    m_dSpeed3D.z = dWindSpeedZ;
}
