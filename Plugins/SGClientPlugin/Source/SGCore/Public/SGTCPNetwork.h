#pragma once
#include "SGMsgReader.h"
#include "Sockets.h"
#include "Networking.h"
#include "SocketSubsystem.h"

class SGCORE_API SGTCPNetwork
{
public:
	SGTCPNetwork()
	{
		m_pMsgReader = MakeShared<SGMsgReader>();
		m_pMsgReciveBuffer = MakeShared<IoBuffer>(1024);
	};
	virtual ~SGTCPNetwork() 
	{ 
		Close(); 
	};

	void Process();
	void Close();
	bool Valid();
	void Destroy();

	bool ConnectTo(const FString& addr, uint16 port, int userdata);

private:

	bool Connect(const FInternetAddr& addr);

	void ReceiveMsg();


private:
	bool m_bDestroyed = false;

	int m_nUserdata = 0;
	FString m_strConnectIP;
	uint16 m_nConnectPort = 0;

	FSocket* m_pSocket = nullptr;
	TSharedPtr<SGMsgReader> m_pMsgReader = nullptr;

	TSharedPtr<IoBuffer> m_pMsgReciveBuffer = nullptr;
	
};
