#pragma once
#include "SingletonBase.h"

#define g_pSndManger  SoundManager::GetInstance()
class SoundManager : public SingletonBase<SoundManager>
{
public:
    SoundManager();
    ~SoundManager();
};

