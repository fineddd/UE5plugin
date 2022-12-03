#include "SGTCPClient.h"

#include "SGMsgBase.pb.h"
#include "MsgID.pb.h"
#include "SGMsgHandler.h"

#include "SGMsgCrypto.h"
#include "SGMsgOther.pb.h"

#define HEART_BEAT_TIMEOUT_MILSECS 25 * 1000
#define HEART_BEAT_SEND_TIME 10 * 1000

void SGTCPClient::Init()
{
    
}

void SGTCPClient::Process()
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
    //heartbeat
    auto nNowTime = FDateTime::Now().ToUnixTimestamp()* 1000 + FDateTime::Now().GetMillisecond();
    if (nNowTime > m_pMsgReader->GetLastReciveMsgTime() + HEART_BEAT_TIMEOUT_MILSECS)
    {
        Close();
        return;
    }
    if (nNowTime > m_nLastSendHeartBeatTime + HEART_BEAT_SEND_TIME)
    {
        SendHeartBeat(nNowTime);
    }
}

void SGTCPClient::Close()
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
    m_pSendMsgheader->Reset();
}

bool SGTCPClient::Valid()
{
    return m_pSocket != nullptr;
}

void SGTCPClient::Destroy()
{
    m_bDestroyed = true;
}

bool SGTCPClient::ConnectTo(const FString& addr, uint16 port)
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
    //todo connect event
    m_strConnectIP = addr;
    m_nConnectPort = port;

    m_nLastSendHeartBeatTime = FDateTime::Now().ToUnixTimestamp();

    GEngine->AddOnScreenDebugMessage(
        -1,
        15.f,
        FColor::Red,
        FString::Printf(TEXT("connect success %s !"), *addr)
    );
    return true;
}

bool SGTCPClient::Send(int nMsgID, std::string& strMsg)
{
    if (m_pSocket == nullptr)
    {
        UE_LOG(SGLog, Error, TEXT("socket null %d"), nMsgID);
        return false;
    }

    if (m_pEnCrypto != nullptr)
    {
        strMsg = m_pEnCrypto->Encrypt(strMsg);
    }
    //todo sgmsg packeter
    m_pSendMsgheader->m_cSerial += 1;
    m_pSendMsgheader->m_nMsgID = nMsgID;
    m_pSendMsgheader->m_uiSize = strMsg.size() + m_pSendMsgheader->GetHeadLength();
    m_pSendMsgheader->mCrcCode = 0;
    //packet header
    m_pMsgSendBuffer->Reset();
    m_pSendMsgheader->EnCode(m_pMsgSendBuffer->GetHead());
    m_pMsgSendBuffer->MoveTail(m_pSendMsgheader->GetHeadLength());
    m_pMsgSendBuffer->Append((const uint8*)strMsg.c_str(), strMsg.size());
    //
    int32 sent = 0;
    return m_pSocket->Send(m_pMsgSendBuffer->GetHead(), m_pMsgSendBuffer->GetSize(), sent);
}
bool SGTCPClient::Send(int nMsgID, google::protobuf::Message& xMsg)
{
	std::string strMsg;
	if (!xMsg.SerializePartialToString(&strMsg))
	{
		UE_LOG(SGLog, Error, TEXT("proto to string error,"), nMsgID);
		return false;
	}
	return Send(nMsgID, strMsg);
}
void SGTCPClient::SetCrypto(bool bEncrypto)
{
    if (bEncrypto)
    {
		//暂时默认使用这种，可以改成配置或参数
		auto pEnCrypto = MakeShared<SGCBlowFish>();
		pEnCrypto->InitBFKey();
		m_pEnCrypto = pEnCrypto;
    }
    else
    {
        m_pEnCrypto = nullptr;
    }
}

bool SGTCPClient::Connect(const FInternetAddr& addr)
{
    return m_pSocket->Connect(addr);
}

void SGTCPClient::ReceiveMsg()
{
    //if (m_pMsgReader == nullptr)
    //{
    //  m_pMsgReader = MakeShared<SGMsgReader>();
    //}
    uint32 DataSize = 0;
    m_pSocket->HasPendingData(DataSize);
    while (DataSize >= m_pMsgReader->GetPendingReciveDataLength())
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
void SGTCPClient::SendHeartBeat(int64_t nNow)
{
	SGMsg::ReqHeartBeat xMsg;
	xMsg.set_attached(1);
	Send(MsgID::MSG_REQ_HEART_BEAT, xMsg);

    m_nLastSendHeartBeatTime = nNow;
    m_pMsgReader->SetHeartBeatTime(nNow);
}