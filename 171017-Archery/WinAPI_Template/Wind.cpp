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
    double dWindSpeedX = ((rand() % 1001) - 500) * 0.0001f;
    double dWindSpeedY = ((rand() % 1001) - 500) * 0.0001f;
    double dWindSpeedZ = ((rand() % 1001) - 500) * 0.0001f;
    m_dSpeed3D.x = dWindSpeedX;
    m_dSpeed3D.y = dWindSpeedY;
    m_dSpeed3D.z = dWindSpeedZ;
#ifdef _DEBUG
    //m_dSpeed3D = UnitSpeed3D{ 0.0f, 0.0f, 0.0f };
#endif // _DEBUG

}
