#include "stdafx.h"
#include "FileDataManager.h"

void FileDataManager::TextSave(char * SaveFilename, vector<string> VecString)
{
    HANDLE hFile;
    char szBuffer[128];
    DWORD write;

    //  String copy to buffer
    strncpy_s(szBuffer, 128, VectorArrayCombine(VecString), 126);

    //  Create file Handle
    hFile = CreateFile(SaveFilename
                        , GENERIC_WRITE
                        , 0
                        , NULL
                        , CREATE_ALWAYS
                        , FILE_ATTRIBUTE_NORMAL
                        , NULL);

    //  Write
    WriteFile(hFile, szBuffer, (DWORD)strlen(szBuffer), &write, NULL);

    //  Close handle
    CloseHandle(hFile);
}

//  CSV format
char * FileDataManager::VectorArrayCombine(vector<string> VecArray)
{
    char szBuffer[128];
    ZeroMemory(szBuffer, sizeof(szBuffer));

    for (int i = 0; i < (int)VecArray.size(); i++)
    {
        strcat_s(szBuffer, VecArray[i].c_str());

        if (i < VecArray.size() - 1)
        {
            strcat_s(szBuffer, ",");
        }
    }

    return szBuffer;
}

vector<string> FileDataManager::TextLoad(char * LoadFilename)
{
    HANDLE hFile;
    char szBuffer[128];
    DWORD read;

    ZeroMemory(szBuffer, strlen(szBuffer));

    //  Create file Handle
    hFile = CreateFile(LoadFilename
        , GENERIC_READ
        , 0
        , NULL
        , OPEN_EXISTING 
        , FILE_ATTRIBUTE_NORMAL
        , NULL);

    //  Read
    ReadFile(hFile, szBuffer, (DWORD)strlen(szBuffer), &read, NULL);

    //  Close handle
    CloseHandle(hFile);

    return CharArraySeperation(szBuffer);
}

vector<string> FileDataManager::CharArraySeperation(char CharArray[])
{
    vector<string> vecArray;
    char* separator = ",";
    char* token;

    token = strtok(CharArray, separator);
    if (token != NULL)
    {
        vecArray.push_back(token);
    }

    while ((token = strtok(NULL, separator)) != NULL)
    {
        vecArray.push_back(token);
    }

    return vecArray;
}