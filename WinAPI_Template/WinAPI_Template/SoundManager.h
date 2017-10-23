#pragma once
#include "SingletonBase.h"

class SoundManager : public SingletonBase<SoundManager>
{
public:
    SoundManager();
    ~SoundManager();
};

