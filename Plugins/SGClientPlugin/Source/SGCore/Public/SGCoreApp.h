#pragma once

#include "SGTypes.h"
#include "SGTCPClient.h"

class SGCORE_API SGCoreApp
{
public:
    virtual ~SGCoreApp();

    static SGCoreApp* GetInstance();


    void Init();
    void Process(float DeltaTime);

    int NewTcpClient();
    void CloseTcpClient(int nIndex);
    TSharedPtr<SGTCPClient> GetTcpClient(int nIndex);

    bool SendMsg(int nMsgID, google::protobuf::Message& xMsg, int nClientIndex = -1);
    //bool Send(int nMsgID, google::protobuf::Message& xMsg);
    template <typename UserClass>
    void RegLoginFinishDelegate(UserClass* pClass, void (UserClass::* UserDelegate)());
	//template <typename UserClass>
	//void RegFakeLoadingFinishDelegate(UserClass* pClass, void (UserClass::* UserDelegate)());

    void DoLoginFinish(/*bool FakeFinish*/);
private:
    SGCoreApp()
    {
        //??
        Init();
    };

    int OnServerTimeRecive(uint32 nClientIndex, uint8* pData, uint32 nLength);
private:
    static SGCoreApp* pCoreApp;

    TMap<int, TSharedPtr<SGTCPClient>> m_mapTcpClient;
    int m_nTcpClientIndex = 0;

    LoginFinishDelegate xLoginFinishDelegate;

    //FakeLoadingFinishDelegate xFakeLoadingFinishDelegate;
    //float nFakeLoadingTime = -1.0;
};

template <typename UserClass>
void SGCoreApp::RegLoginFinishDelegate(UserClass* pClass, void (UserClass::* UserDelegate)())
{
    xLoginFinishDelegate.BindUObject(pClass, UserDelegate);
}
//template <typename UserClass>
//void SGCoreApp::RegFakeLoadingFinishDelegate(UserClass* pClass, void (UserClass::* UserDelegate)())
//{
//    xFakeLoadingFinishDelegate.BindRaw(pClass, UserDelegate);
//}