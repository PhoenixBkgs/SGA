#pragma once
#include "EnumSet.h"

#define L_TARGET_COLOR       0
#define M_TARGEET_COLOR      125
#define S_TARGET_COLOR       200

#define S_TARGET_WIDTH      40
#define M_TARGET_WIDTH      80
#define L_TARGET_WIDTH      120

#define TARGET_THICK        100


class ShootingTarget
{
//  VARS
private:
    E_TARGET_SIZE   m_eTargetSize;
    POINT           m_targetPos;
    

public:
    int     m_targetScore;
    RECT            m_targetRect;
    HBRUSH          m_targetBrush;
    bool            m_isTargetUp;              //  TRUE = ON, FALSE = OFF

//  FUNCS
private:

public:
    ShootingTarget();
    ~ShootingTarget();

    void Setup();
    RECT* GetTargetRect() { return &m_targetRect; }
    void SetTargetUp(bool TargetUpFlag)  { m_isTargetUp = TargetUpFlag; }
    bool GetTargetUp() { return m_isTargetUp; }
    void SetTargetPos(POINT TargetPos)      { m_targetPos = TargetPos; }
    void SetTargetSize(E_TARGET_SIZE TargetSize) { m_eTargetSize = TargetSize; }
    int  GetTargetScore() { return m_targetScore; }

    void CreateTargetRect();
};

