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


struct UnitSize
{
    int w;
    int h;
};

struct RectMargin
{
    int left;
    int top;
    int right;
    int bottom;
};

struct _RGBA
{
    int R;
    int G;
    int B;
    int A;
};