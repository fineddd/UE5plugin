#pragma once
#include "SGMsgReader.h"
#include "Sockets.h"
#include "Networking.h"
#include "SocketSubsystem.h"
#include "SGMsgHeader.h"

#include "google/protobuf/message.h"

class SGIEncrypt;

enum ESGSocketCloseReason
{
    SGSCR_ClientDestroy,
    SGSCR_ActiveClose,
    SGSCR_HeartbeatTimeout,
    SGSCR_NewConnectClose,
    SGSCR_MsgDataError,
};

class SGCORE_API SGTCPClient
{
public:
    SGTCPClient(int nClientIndex)
        : m_nUserdata(nClientIndex)
    {
        m_pMsgReader = MakeShared<SGMsgReader>(nClientIndex);
        m_pMsgReciveBuffer = MakeShared<IoBuffer>(1024);
        m_pMsgSendBuffer = MakeShared<IoBuffer>(1024);
        m_pSendMsgheader = MakeShared<SGClientHeader>();
    };
    virtual ~SGTCPClient()
    {
        Close(SGSCR_ClientDestroy);
    };

    void Init();
    void Process();
    void Close(int nCloseReasn);
    bool Valid();
    void Destroy();

    bool ConnectTo(const FString& addr, uint16 port);

    bool Send(int nMsgID, std::string& strMsg);

    bool Send(int nMsgID, google::protobuf::Message& xMsg);
    void SetCrypto(bool bEncrypto);

private:

    bool Connect(const FInternetAddr& addr);

    void ReceiveMsg();

    void SendHeartbeat(int64_t nNow);

private:
    bool m_bDestroyed = false;

    int m_nUserdata = 0;

    FString m_strConnectIP;
    uint16 m_nConnectPort = 0;

    FSocket* m_pSocket = nullptr;
    TSharedPtr<SGMsgReader> m_pMsgReader = nullptr;
    TSharedPtr<IoBuffer> m_pMsgReciveBuffer = nullptr;
    //
    TSharedPtr<IoBuffer> m_pMsgSendBuffer = nullptr;
    TSharedPtr<SGClientHeader> m_pSendMsgheader;
    TSharedPtr<SGIEncrypt> m_pEnCrypto = nullptr;
    //heart beat
    int64_t m_nLastSendHeartbeatTime;
};
