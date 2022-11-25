#pragma once

#include "SGTypes.h"
#include "SGTCPNetwork.h"

class SGCORE_API SGCoreApp
{
public:
	virtual ~SGCoreApp() {};

	static SGCoreApp* GetInstance();

	void Process();

	TSharedPtr<SGTCPNetwork> GetTcpNetwork();

private:
	SGCoreApp()
	{
		m_pTcpNetwork = MakeShared<SGTCPNetwork>();
	};

private:
	static SGCoreApp* pCoreApp;

	TSharedPtr<SGTCPNetwork> m_pTcpNetwork;
};