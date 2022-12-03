#pragma once

#include "SGTypes.h"
#include "SGTCPClient.h"

class SGCORE_API SGCoreApp
{
public:
    virtual ~SGCoreApp() {};

    static SGCoreApp* GetInstance();


    void Init();
    void Process();

    int NewTcpClient();
    void CloseTcpClient(int nIndex);
    TSharedPtr<SGTCPClient> GetTcpClient(int nIndex);



private:
    SGCoreApp()
    {
        //??
        Init();
    };

private:
    static SGCoreApp* pCoreApp;

    TMap<int, TSharedPtr<SGTCPClient>> m_mapTcpClient;
    int m_nTcpClientIndex = 0;
};