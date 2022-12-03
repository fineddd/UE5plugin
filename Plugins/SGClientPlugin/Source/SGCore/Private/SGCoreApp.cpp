#include "SGCoreApp.h"


SGCoreApp* SGCoreApp::pCoreApp = nullptr;

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
}

void SGCoreApp::Process()
{
    for (auto& [_, pClient] : m_mapTcpClient)
    {
        pClient->Process();
    }
}
int SGCoreApp::NewTcpClient()
{
    auto pTcpClient = MakeShared<SGTCPClient>(m_nTcpClientIndex);
    pTcpClient->Init();
    m_mapTcpClient.Add(m_nTcpClientIndex, pTcpClient);
    UE_LOG(SGLog, Log, TEXT("new tcp client %d"), m_nTcpClientIndex);
    return m_nTcpClientIndex++;
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