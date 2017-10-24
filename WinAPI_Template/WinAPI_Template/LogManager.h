#pragma once

#include "SingletonBase.h"
#include <fstream>

#define g_pLogManager LogManager::GetInstance()

enum LOG_LEVEL
{
    EL_DEBUG = 0, EL_INFO, EL_ALERT
};

class LogManager : public SingletonBase<LogManager>
{
private:
    string m_szLogPath;
    string m_szLogFilename;

    void CreateLogDir();

    string GetTimeString();
    string GetCurrentPath();

public:

    void Setup(string LogPath);
    void WriteLog(LOG_LEVEL LogLevel, string Message);
};

