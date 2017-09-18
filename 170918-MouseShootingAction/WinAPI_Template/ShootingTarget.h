#pragma once
#include "EnumSet.h"

#define L_TARGET_COLOR       0
#define M_TARGEET_COLOR      125
#define S_TARGET_COLOR       253

#define S_TARGET_WIDTH      10
#define S_TARGET_HEIGHT     20
#define M_TARGET_WIDTH      20
#define M_TARGET_HEIGHT     40
#define L_TARGET_WIDTH      80
#define L_TARGET_HEIGHT     160

#define TARGET_THICK        5


class ShootingTarget
{
//  VARS
private:
    E_TARGET_SIZE   m_eTargetSize;
    RECT            m_targetRect;
    HBRUSH          m_targetBrush;
    bool            m_isTargetUp;              //  TRUE = ON, FALSE = OFF
    POINT           m_targetPos;
    
    int     m_targetScore;

public:

//  FUNCS
private:

public:
    ShootingTarget();
    ~ShootingTarget();

    void Setup();
    RECT GetTargetRect() { return m_targetRect; }
    void SetTagetUpFlag(bool TargetUpFlag)  { m_isTargetUp = TargetUpFlag; }
    void SetTargetPos(POINT TargetPos)      { m_targetPos = TargetPos; }
    void SetTargetSize(E_TARGET_SIZE TargetSize) { m_eTargetSize = TargetSize; }

    void CreateTargetRect(HDC* hdc);
};

