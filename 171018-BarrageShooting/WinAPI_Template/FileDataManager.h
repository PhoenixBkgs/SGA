#pragma once
#include "SingletonBase.h"

#define g_pFileManager FileDataManager::GetInstance()

class FileDataManager : public SingletonBase<FileDataManager>
{
private:
    char*   VectorArrayCombine(vector<string> VecArray);
    vector<string>  CharArraySeperation(char CharArray[]);
public:
    void    TextSave(char* SaveFilename, vector<string> VecString);
    vector<string>  TextLoad(char* LoadFilename);

    void    JsonLoad(string szFilename);
    void    JsonSave(string szFilename, string szJsonData);
};