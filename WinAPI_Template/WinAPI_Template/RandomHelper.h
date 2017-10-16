#pragma once
class RandomHelper
{
private:

public:
    RandomHelper();
    ~RandomHelper();

    int GetRandomNumber();
    int GetRandomNumber(bool IsReverseSign);
    int GetRandomNumber(int Max, bool IsReverseSign);
    int GetRandomNumber(int Begin, int End, bool IsReverseSign);

    

};

