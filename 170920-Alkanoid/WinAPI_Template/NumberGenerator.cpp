#include "stdafx.h"
#include "NumberGenerator.h"


NumberGenerator::NumberGenerator()
{
}


NumberGenerator::~NumberGenerator()
{
}

int NumberGenerator::GetRandomNumber()
{
    srand(time(NULL));
    return rand();
}

int NumberGenerator::GetRandomNumber(bool IsReverseSign)
{
    int retRandomNumber = GetRandomNumber();
    if (IsReverseSign)
    {
        retRandomNumber = -retRandomNumber;
    }

    return retRandomNumber;
}

int NumberGenerator::GetRandomNumber(int Max, bool IsReverseSign)
{
    int retRandomNumber = GetRandomNumber() % Max;
    if (IsReverseSign)
    {
        retRandomNumber = -retRandomNumber;
    }

    return retRandomNumber;
}

int NumberGenerator::GetRandomNumber(int Begin, int End, bool IsReverseSign)
{
    int retRandomNumber = (GetRandomNumber() % (End - Begin) + Begin);

    if (IsReverseSign)
    {
        retRandomNumber = -retRandomNumber;
    }

    return retRandomNumber;
}

