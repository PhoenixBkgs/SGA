#pragma once
class NumberGenerator
{
private:

public:
    NumberGenerator();
    ~NumberGenerator();

    int GetRandomNumber();
    int GetRandomNumber(bool IsReverseSign);
    int GetRandomNumber(int Max, bool IsReverseSign);
    int GetRandomNumber(int Begin, int End, bool IsReverseSign);

    

};

