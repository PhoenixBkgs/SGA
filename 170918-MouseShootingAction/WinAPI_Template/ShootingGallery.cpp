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
        //  ���� Ÿ�� ����
        for (int smallIdx = 0; smallIdx < m_smallTargetCount; smallIdx++)
        {
        }
        //  �߰� Ÿ�� ����
        for (int mediumIdx = 0; mediumIdx < m_mediumTargetCount; mediumIdx++)
        {

        }
        //  ū Ÿ�� ����
        for (int largeIdx = 0; largeIdx < m_largeTargetCount; largeIdx++)
        {

        }
    }
}
