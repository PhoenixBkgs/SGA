#pragma once
#include "SingletonBase.h"

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "EndOfFile")  

#include <oledb.h>  
#include <stdio.h>  
#include <conio.h>  
#include "icrsint.h" 
class DbManager : public SingletonBase<DbManager>
{
private:

public:

};

class CAdo
{
private:
    BOOL m_bIsConnected;
    HRESULT m_hresult;
    _ConnectionPtr m_pConn;
    _RecordsetPtr m_pRset;

public:
    CAdo();
    virtual ~CAdo();

    void* SQLExecute(char *szSQL);
    BOOL SQLDelete(char *szTableName, char *szWhere);
    BOOL SQLUpdate(char* szTableName, char* szSet, char* szWhere);
    _RecordsetPtr SQLSelect(char* szTableName);
    BOOL SQLInsert(char* szTableName, char* szValues);
    BOOL Disconnect();
    BOOL Connect(char* szDBServerIP, char* szDBName, char* szUserID, char* szUserPW);


};