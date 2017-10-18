#include "stdafx.h"
#include "GeometryHelper.h"

UnitPos GeometryHelper::GetCenterPointWindow()
{
    return UnitPos{ W_WIDTH * 0.5, W_HEIGHT * 0.5 };
}

double GeometryHelper::GetVectorSpeed(UnitPos BeginPos, UnitPos DestPos)
{
    double speedX = DestPos.x - BeginPos.x;
    double speedY = DestPos.y - BeginPos.y;

    double retVSpeed = sqrt(sq(speedX) + sq(speedY));

    return retVSpeed;
}

UnitPos GeometryHelper::GetCoordFromAngle(double Degree, double Length)
{
    double x = Length * sin(Degree2Rad(Degree));
    double y = Length * cos(Degree2Rad(Degree));
    return UnitPos{ x, y };
}

double GeometryHelper::GetAngleFromCoord(UnitPos BeginPos, UnitPos DestPos)
{
    double x = DestPos.x - BeginPos.x;
    double y = DestPos.y - BeginPos.y;

    double angle = atan2(y, x);
    angle = Rad2Degree(angle);
    angle *= -1.0f;
    angle += 90.0f;
    return angle;
}

double GeometryHelper::Degree2Rad(double Degree)
{
#ifdef _DEBUG
    double retVal = Degree * M_PI / 180;
    return retVal;
#else
    //  RELEASE
    return Degree * M_PI / 180;
#endif

}

double GeometryHelper::Rad2Degree(double Rad)
{
    double retVal = Rad * 180 / M_PI;
    return retVal;
}

double GeometryHelper::GetDistance(UnitPos Pos1, UnitPos Pos2)
{
    double dX = abs(Pos1.x - Pos2.x);
    double dY = abs(Pos1.y - Pos2.y);

    dX *= dX;
    dY *= dY;

    return sqrt(dX + dY);
}

UnitPos GeometryHelper::GetRotateCoord(UnitPos StartPos, UnitPos DestPos, double DeltaDegree)
{
#ifdef _DEBUG
    //DeltaDegree = Degree2Rad(DeltaDegree);
    double dist = GetDistance(StartPos, DestPos);
    double currAngle = GetAngleFromCoord(StartPos, DestPos);
    double destAngle = currAngle + DeltaDegree;
    UnitPos resultPos = GetCoordFromAngle(destAngle, dist);
    resultPos.x += StartPos.x;
    resultPos.y += StartPos.y;
    return resultPos;
#else
    //  RELEASE
    return GetCoordFromAngle(GetAngleFromCoord(StartPos, DestPos) + DeltaDegree, GetDistance(StartPos, DestPos));
#endif
}
