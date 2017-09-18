#include "stdafx.h"
#include "ShootingGallery.h"


ShootingGallery::ShootingGallery()
{
}


ShootingGallery::~ShootingGallery()
{
}

void ShootingGallery::SetupTargets()
{
    int entireTargetCount = m_smallTargetCount + m_mediumTargetCount + m_largeTargetCount;

    ShootingTarget target;
    for (int i = 0; i < entireTargetCount; i++)
    {
        //  累篮 鸥百 积己
        for (int smallIdx = 0; smallIdx < m_smallTargetCount; smallIdx++)
        {
        }
        //  吝埃 鸥百 积己
        for (int mediumIdx = 0; mediumIdx < m_mediumTargetCount; mediumIdx++)
        {

        }
        //  奴 鸥百 积己
        for (int largeIdx = 0; largeIdx < m_largeTargetCount; largeIdx++)
        {

        }
    }
}
