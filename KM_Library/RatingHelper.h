#pragma once

#define CONST_K 32
class RatingHelper
{
public:
    RatingHelper();
    ~RatingHelper();

    void EloCalc(int* Rating1, int* Rating2, int Winner);
};

