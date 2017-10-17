#pragma once

struct UnitPos
{
    double x;
    double y;
};
typedef UnitPos UnitSpeed;

struct UnitPos3D
{
    double x;
    double y;
    double z;
};
typedef UnitPos3D UnitSpeed3D;


struct UnitSize
{
    int w;
    int h;
};

struct _RGBA
{
    int R;
    int G;
    int B;
    int A;
};