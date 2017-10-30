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