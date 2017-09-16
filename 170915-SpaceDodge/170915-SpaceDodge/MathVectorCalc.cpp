#include "stdafx.h"
#include "MathVectorCalc.h"


MathVectorCalc::MathVectorCalc()
{
}


MathVectorCalc::~MathVectorCalc()
{
}

vector<double> MathVectorCalc::GetDirection(POINT destPt, POINT startPt, double speed)
{
    vector<double> direction;
    direction.push_back((destPt.x - startPt.x) * speed);
    direction.push_back((destPt.y - startPt.y) * speed);

    return direction;
}
