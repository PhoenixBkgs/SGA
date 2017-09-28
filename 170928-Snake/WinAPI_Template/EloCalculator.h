#pragma once

#define CONST_K 32
class EloCalculator
{
public:
    EloCalculator();
    ~EloCalculator();

    void EloCalc(int* Rating1, int* Rating2, int Winner);
};

