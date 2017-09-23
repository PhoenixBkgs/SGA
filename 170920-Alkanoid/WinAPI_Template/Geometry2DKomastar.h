#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

inline double sq(double x) { return x * x; }

class Geometry2DKomastar
{
public:
    Geometry2DKomastar();
    ~Geometry2DKomastar();

    UnitPos GetCenterPointWindow();

    double GetVectorSpeed(UnitPos BeginPos, UnitPos DestPos);
    UnitPos GetCoordFromAngle(double Degree, double Length);
    double GetAngleFromCoord(UnitPos BeginPos, UnitPos DestPos);
    double Degree2Rad(double Degree);
    double Rad2Degree(double Rad);
};

