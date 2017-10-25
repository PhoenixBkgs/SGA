#pragma once
#include "SingletonBase.h"

#define g_pFileManager FileDataManager::GetInstance()

class FileDataManager : public SingletonBase<FileDataManager>
{
public:
    void    JsonSave(string Filename, string JsonString);
    void    FileAppend(string Filename, string StringData);

    void    TextSave(char* SaveFilename, vector<string> VecString);
    char*   VectorArrayCombine(vector<string> VecArray);
    string  MakeCsvString(vector<string> VecArray);
    vector<string>  TextLoad(char* LoadFilename);
    vector<string>  CharArraySeperation(char CharArray[]);
};