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

void FileDataManager::Tokenizer(const string & str, vector<string>& tokens, const string & token)
{
    // �� ù ���ڰ� �������� ��� ����
    string::size_type lastPos = str.find_first_not_of(token, 0);
    // �����ڰ� �ƴ� ù ���ڸ� ã�´�
    string::size_type pos = str.find_first_of(token, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // token�� ã������ vector�� �߰��Ѵ�
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // �����ڸ� �پ�Ѵ´�.  "not_of"�� �����϶�
        lastPos = str.find_first_not_of(token, pos);
        // ���� �����ڰ� �ƴ� ���ڸ� ã�´�
        pos = str.find_first_of(token, lastPos);
    }
}
