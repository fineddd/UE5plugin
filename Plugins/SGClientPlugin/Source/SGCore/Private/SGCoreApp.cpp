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

void SGCoreApp::Process()
{
	m_pTcpNetwork->Process();
}

TSharedPtr<SGTCPNetwork> SGCoreApp::GetTcpNetwork()
{
	return m_pTcpNetwork;
}
