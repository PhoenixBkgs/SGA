#pragma once
#include "SingletonBase.h"

#define g_pFileManager FileDataManager::GetInstance()

class FileDataManager : public SingletonBase<FileDataManager>
{
public:
    void    JsonSave(string Filename, string JsonString);
    void    FileAppend(string Filename, string StringData);

    string  MakeCsvString(vector<string> VecArray);
    vector<string>  CharArraySeperation(char CharArray[]);
    void Tokenizer(const string& str, vector<string>& tokens, const string& token = ",");
};