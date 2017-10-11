#include "stdafx.h"
#include "Geometry2DKomastar.h"

Geometry2DKomastar::Geometry2DKomastar()
{
}


Geometry2DKomastar::~Geometry2DKomastar()
{
    
}

UnitPos Geometry2DKomastar::GetCenterPointWindow()
{
    return UnitPos{ W_WIDTH * 0.5, W_HEIGHT * 0.5 };
}

double Geometry2DKomastar::GetVectorSpeed(UnitPos BeginPos, UnitPos DestPos)
{
    double speedX = DestPos.x - BeginPos.x;
    double speedY = DestPos.y - BeginPos.y;

    double retVSpeed = sqrt(sq(speedX) + sq(speedY));

    return retVSpeed;
}

UnitPos Geometry2DKomastar::GetCoordFromAngle(double Degree, double Length)
{
    double x = Length * sin(Degree2Rad(Degree));
    double y = Length * cos(Degree2Rad(Degree));
    return UnitPos{ x, y };
}

double Geometry2DKomastar::GetAngleFromCoord(UnitPos BeginPos, UnitPos DestPos)
{
    double x = DestPos.x - BeginPos.x;
    double y = DestPos.y - BeginPos.y;

    double angle = atan2(y, x);
    angle = Rad2Degree(angle);
    angle *= -1.0f;
    angle += 90.0f;
    return angle;
}

double Geometry2DKomastar::Degree2Rad(double Degree)
{
    double retVal = Degree * M_PI / 180;
    return retVal;
}

double Geometry2DKomastar::Rad2Degree(double Rad)
{
    double retVal = Rad * 180 / M_PI;
    return retVal;
}

double Geometry2DKomastar::GetDistance(UnitPos Pos1, UnitPos Pos2)
{
    double dX = abs(Pos1.x - Pos2.x);
    double dY = abs(Pos1.y - Pos2.y);

    dX *= dX;
    dY *= dY;

    return sqrt(dX + dY);
}
