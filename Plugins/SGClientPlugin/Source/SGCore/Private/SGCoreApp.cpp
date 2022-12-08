#include "SGCoreApp.h"

#include "SGMsgOther.pb.h"
#include "SGMsgHandler.h"

#include "MsgID.pb.h"

SGCoreApp* SGCoreApp::pCoreApp = nullptr;

SGCoreApp::~SGCoreApp()
{
    SGMsgHandler::GetInstance()->UnRegMsgDelegate(MsgID::MSG_S2C_NTF_SERVER_TIME);
}

SGCoreApp* SGCoreApp::GetInstance()
{
    if (pCoreApp != nullptr)
    {
        return pCoreApp;
    }
    pCoreApp = new SGCoreApp();
    return pCoreApp;
}

void SGCoreApp::Init()
{
    SGMsgHandler::GetInstance()->RegMsgRowDelegate(MsgID::MSG_S2C_NTF_SERVER_TIME, this, &SGCoreApp::OnServerTimeRecive);
}

void SGCoreApp::Process(float DeltaTime)
{
    for (auto& [_, pClient] : m_mapTcpClient)
    {
        pClient->Process();
    }
    //if (nFakeLoadingTime > 0)
    //{
    //    nFakeLoadingTime = nFakeLoadingTime - DeltaTime;
    //    if (nFakeLoadingTime <= 0)
    //    {
    //        xFakeLoadingFinishDelegate.ExecuteIfBound();
    //    }
    //}
}
int SGCoreApp::NewTcpClient()
{
    ++m_nTcpClientIndex;
    auto pTcpClient = MakeShared<SGTCPClient>(m_nTcpClientIndex);
    pTcpClient->Init();
    m_mapTcpClient.Add(m_nTcpClientIndex, pTcpClient);
    UE_LOG(SGLog, Log, TEXT("new tcp client %d"), m_nTcpClientIndex);
    return m_nTcpClientIndex;
}
void SGCoreApp::CloseTcpClient(int nIndex)
{
    //auto pClient = m_mapTcpClient.Find(nIndex);
    //if (pClient == nullptr)
    //{
    //    return;
    //}
    m_mapTcpClient.Remove(nIndex);
}
TSharedPtr<SGTCPClient> SGCoreApp::GetTcpClient(int nIndex)
{
    auto pClient = m_mapTcpClient.Find(nIndex);
    if (pClient == nullptr)
    {
        return nullptr;
    }
    return *pClient;
}
bool SGCoreApp::SendMsg(int nMsgID, google::protobuf::Message& xMsg, int nClientIndex)
{
    if (nClientIndex == -1)
    {
        nClientIndex = m_nTcpClientIndex;
    }
    auto pClient = GetTcpClient(nClientIndex);
    if (pClient == nullptr)
    {
		UE_LOG(SGLog, Error, TEXT("tcp client null %d"), nClientIndex);
        return false;
    }
    return pClient->Send(nMsgID, xMsg);
}
//bool SGCoreApp::Send(int nMsgID, google::protobuf::Message& xMsg)
//{
//    return Send(m_nTcpClientIndex, nMsgID, xMsg);
//}
void SGCoreApp::DoLoginFinish(/*bool FakeFinish*/)
{
    //if (!FakeFinish)
    //{
    xLoginFinishDelegate.ExecuteIfBound();
    //}
    //nFakeLoadingTime = 10.0;
}
int SGCoreApp::OnServerTimeRecive(uint32 nClientIndex, uint8* pData, uint32 nLength)
{
    SGMsg::S2CNtfServerTime xTimeMsg;
    if (!xTimeMsg.ParseFromArray(pData, nLength))
    {
        UE_LOG(SGLog, Error, TEXT("server timemsg error %d"), nClientIndex);
        return 1;
    }
    SGToolFun::nServerDeltaTime = xTimeMsg.server_time() - FDateTime::Now().ToUnixTimestamp() * 1000 + FDateTime::Now().GetMillisecond();

    return 0;
}
