#pragma once

#include "SingletonBase.h"
#include <fstream>

enum LOG_LEVEL
{
    EL_DEBUG = 0, EL_INFO, EL_ALERT
};

class Log4Komastar : public SingletonBase<Log4Komastar>
{
private:
    ofstream m_streamLog;
    string m_szLogPath;
    string m_szLogFilename;

    void CreateLogDir();

    string GetTimeString();
    string GetCurrentPath();

public:
    Log4Komastar();
    ~Log4Komastar();

    void Setup(string LogPath);
    void WriteLog(LOG_LEVEL LogLevel, string Message);
};

