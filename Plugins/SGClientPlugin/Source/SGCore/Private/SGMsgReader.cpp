#include "SGMsgReader.h"
#include "SGMsgHandler.h"
#include "MsgID.pb.h"
#include "SGMsgOther.pb.h"

bool SGMsgReader::Process(uint8* pData, uint32 nLength)
{
    m_pMsgBuff->Append(pData, nLength);
    while (m_pMsgBuff->GetSize() >= m_nNextReciveDataLength)
    {
        switch (m_nState)
        {
        case MRS_HeadType:
            {
			    if (InitHeader(*m_pMsgBuff->GetHead()) == nullptr)
			    {
				    return false;
			    }
                //m_pMsgBuff->MoveHead(1);
                m_nState = MRS_Head;
                m_nNextReciveDataLength = m_pMsgheader->GetHeadLength();
            }
            break;
        case MRS_Head:
            {
                //if (m_pMsgBuff->GetSize() < m_pMsgheader->GetHeadLength())
                //{
                //    return true;
                //}
                m_pMsgheader->DeCode(m_pMsgBuff->GetHead() + 1);
                m_pMsgBuff->MoveHead(m_pMsgheader->GetHeadLength());

                m_nState = MRS_Body;
                m_nNextReciveDataLength = m_pMsgheader->GetMsgLength() - m_pMsgheader->GetHeadLength();
            }
            break;
        case MRS_Body:
            {
                //if (m_pMsgBuff->GetSize() < m_pMsgheader->GetMsgLength() - m_pMsgheader->GetHeadLength())
                //{
                //    return true;
                //}
                OnReciveMsg();
                m_pMsgBuff->MoveHead(m_pMsgheader->GetMsgLength() - m_pMsgheader->GetHeadLength());
                m_nState = MRS_HeadType;
                m_nNextReciveDataLength = 1;
            }
            break;
        default:
            break;
        }
    }
    return true;
}

TSharedPtr<SGMsgHeaderBase> SGMsgReader::InitHeader(uint8 nHeadType)
{
    switch (nHeadType)
    {
    case MHT_ClientToServer:
        {
            if (m_pMsgheader != nullptr && m_pMsgheader->GetHeadType() == nHeadType)
            {
                m_pMsgheader->Reset();
            }
            else
            {
                m_pMsgheader = MakeShared<SGClientHeader>();
            }
        }
        break;
    case MHT_ServerToClient:
        {
            if (m_pMsgheader != nullptr && m_pMsgheader->GetHeadType() == nHeadType)
            {
                m_pMsgheader->Reset();
            }
            else
            {
                m_pMsgheader = MakeShared<SGServerHeader>();
            }
        }
        break;
    default:
        return nullptr;
    }
    return m_pMsgheader;
}

void SGMsgReader::Reset()
{
    m_nState = MRS_HeadType;
}

void SGMsgReader::OnReciveMsg()
{
    if (m_pMsgheader->GetMsgID() == MsgID::MSG_RSP_HEART_BEAT)
    {
        m_nReciveHeartbeatTime = SGToolFun::GetNowMilTimeStamp();
		SGMsg::RspHeartBeat xMsg;
		if (!xMsg.ParseFromArray(m_pMsgBuff->GetHead(), m_pMsgheader->GetMsgLength() - m_pMsgheader->GetHeadLength()))
		{
			return;
		}
        m_nMsgDelay = xMsg.server_time() - m_nSendHeartbeatTime;
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("heartbeat recive %d"), m_nMsgDelay)
		);
        return;
    }
    SGMsgHandler::GetInstance()->OnRecvMsg(m_pMsgheader->GetMsgID(), m_nClientIndex, m_pMsgBuff->GetHead(), m_pMsgheader->GetMsgLength() - m_pMsgheader->GetHeadLength());
}
//void SGMsgReader::SetClientIndex(uint32 nClientIndex)
//{
//    m_nClientIndex = nClientIndex;
//}
int32 SGMsgReader::GetPendingReciveDataLength()
{
    return m_nNextReciveDataLength - m_pMsgBuff->GetSize();
}
int64_t SGMsgReader::GetLastReciveHeartbeatTime()
{
    return m_nReciveHeartbeatTime;
}
void SGMsgReader::SetLastReciveHeartbeatTime(int64_t nLastTime)
{
    m_nReciveHeartbeatTime = nLastTime;
}
void SGMsgReader::SetHeartbeatTime(int64_t nTime)
{
    m_nSendHeartbeatTime = nTime;
}
int64_t SGMsgReader::GetMsgDelayTime()
{
    return m_nMsgDelay;
}