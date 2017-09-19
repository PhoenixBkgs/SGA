#include "stdafx.h"
#include "Log4Komastar.h"

Log4Komastar::Log4Komastar()
{
}


Log4Komastar::~Log4Komastar()
{
}

void Log4Komastar::CreateLogDir()
{
    if (CreateDirectory(m_szLogPath.c_str(), NULL) ||
        ERROR_ALREADY_EXISTS == GetLastError())
    {
        // CopyFile(...)
        cout << "SUC" << endl;
    }
    else
    {
        // Failed to create directory.
        cout << "FAILED" << endl;
    }
}

string Log4Komastar::GetTimeString()
{
    time_t rawTime;
    struct tm now;
    char buffer[80];
    
    time(&rawTime);
    localtime_s(&now, &rawTime);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %I:%M:%S", &now);
    string retTimeString(buffer);

    return retTimeString;
}

string Log4Komastar::GetCurrentPath()
{
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");

    return string(buffer).substr(0, pos);
}

void Log4Komastar::Setup(string LogPath)
{
    m_szLogPath = GetCurrentPath();
    m_szLogPath.append(LogPath);
    CreateLogDir();
    m_szLogFilename = m_szLogPath + "\\Log.txt";
}

void Log4Komastar::WriteLog(LOG_LEVEL LogLevel, string Message)
{
    string szLog = "";
    string szJoint = "";
    szLog.append(GetTimeString());
    switch (LogLevel)
    {
    case EL_DEBUG:
        szJoint = "[DEBUG]";
        break;
    case EL_INFO:
        szJoint = "[INFO]";
        break;
    case EL_ALERT:
        szJoint = "[ALERT]";
        break;
    }
    szLog.append(szJoint);
    szLog.append(Message + "\n");

    m_streamLog.open(m_szLogFilename, ios_base::app);
    m_streamLog << szLog;
    m_streamLog.close();
}
