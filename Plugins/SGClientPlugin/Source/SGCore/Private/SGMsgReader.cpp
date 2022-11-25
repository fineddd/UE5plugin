#include "SGMsgReader.h"
#include "SGMsgHandler.h"
#include "MsgID.pb.h"

bool SGMsgReader::Process(uint8* pData, uint32 nLength)
{
	m_pMsgBuff->Append(pData, nLength);
	while (m_pMsgBuff->GetSize() > 0)
	{
		switch (m_nState)
		{
			case MRS_HeadType:
			{
				if (InitHeader(*m_pMsgBuff->GetHead()) == nullptr)
				{
					return false;
				}
				m_pMsgBuff->MoveHead(1);
				m_nState = MRS_Head;
			}
			break;
			case MRS_Head:
			{
				if (m_pMsgBuff->GetSize() < m_pMsgheader->GetHeadLength() - 1)
				{
					return true;
				}
				m_pMsgheader->DeCode(m_pMsgBuff->GetHead());
				m_pMsgBuff->MoveHead(m_pMsgheader->GetHeadLength() - 1);
				m_nState = MRS_Body;
			}
			break;
			case MRS_Body:
			{
				if (m_pMsgBuff->GetSize() < m_pMsgheader->GetMsgLength())
				{
					return true;
				}
				OnReciveMsg();
				m_pMsgBuff->MoveHead(m_pMsgheader->GetMsgLength());
				m_nState = MRS_Head;
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
		//todo beat heart
		return;
	}
	SGMsgHandler::GetInstance()->OnRecvMsg(m_pMsgheader->GetMsgID(), m_pMsgBuff->GetHead(), m_pMsgheader->GetMsgLength());
}
