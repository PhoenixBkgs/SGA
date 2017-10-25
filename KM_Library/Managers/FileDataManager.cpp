#include "stdafx.h"
#include "FileDataManager.h"

void FileDataManager::JsonSave(string Filename, string JsonString)
{
    ofstream fileOut;
    fileOut.open(Filename, ios_base::out);
    fileOut << JsonString;
    fileOut.close();
}

void FileDataManager::FileAppend(string Filename, string StringData)
{
    ofstream fileOut;
    fileOut.open(Filename, ios_base::app);
    fileOut << StringData;
    fileOut.close();
}

void FileDataManager::TextSave(char * SaveFilename, vector<string> VecString)
{
    HANDLE hFile;
    string szBuffer;
    DWORD write;

    //  String copy to buffer
    //strncpy_s(szBuffer, 128, VectorArrayCombine(VecString), 126);
    szBuffer = VectorArrayCombine(VecString);

    //  Create file Handle
    hFile = CreateFile(SaveFilename
                        , GENERIC_WRITE
                        , 0
                        , NULL
                        , CREATE_ALWAYS
                        , FILE_ATTRIBUTE_NORMAL
                        , NULL);

    //  Write
    WriteFile(hFile, szBuffer.c_str(), (DWORD)strlen(szBuffer.c_str()), &write, NULL);

    //  Close handle
    CloseHandle(hFile);
}

string FileDataManager::MakeCsvString(vector<string> VecArray)
{
    string szBuffer = "";

    for (int i = 0; i < (int)VecArray.size(); i++)
    {
        szBuffer.append(VecArray[i]);
        szBuffer.append(",");
    }

    return szBuffer;
}

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
    char* temp = NULL;
    char* separator = ",";
    char* token;

    token = strtok_s(CharArray, separator, &temp);
    if (token != NULL)
    {
        vecArray.push_back(token);
    }

    while ((token = strtok_s(NULL, separator, &temp)) != NULL)
    {
        vecArray.push_back(token);
    }

    return vecArray;
}