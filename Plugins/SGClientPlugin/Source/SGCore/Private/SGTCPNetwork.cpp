#include "SGTCPNetwork.h"
#include "Logging/LogMacros.h"

void SGTCPNetwork::Process()
{
	if (m_bDestroyed)
	{
		Close();
		delete this;
		return;
	}
	if (!Valid())
	{
		return;
	}
	//recive msg
	ReceiveMsg();
	//send msg
	//heartbeat
}

void SGTCPNetwork::Close()
{
	if (m_pSocket != nullptr)
	{
		m_pSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(m_pSocket);
		//todo close event
		m_pSocket = nullptr;
	}
	m_strConnectIP = TEXT("");
	m_nConnectPort = 0;
	m_nUserdata = 0;
	m_pMsgReader->Reset();
}

bool SGTCPNetwork::Valid()
{
	return m_pSocket != nullptr;
}

void SGTCPNetwork::Destroy()
{
	m_bDestroyed = true;
}

bool SGTCPNetwork::ConnectTo(const FString& addr, uint16 port, int userdata)
{
	Close();

	FIPv4Address ip;
	uint32 OutIP = 0;

	if (!FIPv4Address::Parse(addr, ip))
	{
		auto resolveInfo = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetHostByName(TCHAR_TO_ANSI(*addr));
		while (!resolveInfo->IsComplete());

		if (resolveInfo->GetErrorCode() != 0)
		{
			UE_LOG(SGLog, Error, TEXT("tcp connect to get resolveinfo error %s, code=%d"), *addr, resolveInfo->GetErrorCode());
			return false;
		}

		resolveInfo->GetResolvedAddress().GetIp(OutIP);
	}
	else
	{
		OutIP = ip.Value;
	}


	TSharedRef<FInternetAddr> internetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	internetAddr->SetIp(OutIP);
	internetAddr->SetPort(port);

	m_pSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	if (m_pSocket == nullptr)
	{
		return false;
	}
	if (!m_pSocket->SetNonBlocking(true))
	{
		UE_LOG(SGLog, Warning, TEXT("socket no blocking error"));
	}
	if (!Connect(*internetAddr))
	{
		return false;
	}
	m_strConnectIP = addr;
	m_nConnectPort = port;
	m_nUserdata = userdata;

	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Red,
		FString::Printf(TEXT("connect finish %s !"), *addr)
	);
	return true;
}

bool SGTCPNetwork::Connect(const FInternetAddr& addr)
{
	return m_pSocket->Connect(addr);
}

void SGTCPNetwork::ReceiveMsg()
{
	//if (m_pMsgReader == nullptr)
	//{
	//	m_pMsgReader = MakeShared<SGMsgReader>();
	//}
	uint32 DataSize = 0;
	m_pSocket->HasPendingData(DataSize);
	while (DataSize > 0)
	{
		m_pMsgReciveBuffer->Reset();
		m_pMsgReciveBuffer->Reserve(FMath::Min(DataSize, 65507u));
		int32 BytesRead = 0;
		if (m_pSocket->Recv(m_pMsgReciveBuffer->GetTail(), m_pMsgReciveBuffer->GetFreeSize(), BytesRead))
		{
			m_pMsgReciveBuffer->MoveTail(BytesRead);
			if (!m_pMsgReader->Process(m_pMsgReciveBuffer->GetHead(), BytesRead))
			{
				Close();
				UE_LOG(SGLog, Error, TEXT("process buffer data error, net close"));
				return;
			}
		}
		DataSize = DataSize - BytesRead;
	}
}
