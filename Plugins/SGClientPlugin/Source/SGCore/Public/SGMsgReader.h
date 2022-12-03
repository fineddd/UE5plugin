#pragma once

#include "SGTypes.h"
#include "IOBuffer.h"
#include "SGMsgHeader.h"

class SGCORE_API SGMsgReader
{
public:
	SGMsgReader(uint32 nClientIndex)
		:m_nClientIndex(nClientIndex)
	{
		m_pMsgBuff = MakeShared<IoBuffer>(1024*1024);
	};
	virtual ~SGMsgReader() {};

	bool Process(uint8* pData, uint32 nLength);

	TSharedPtr<SGMsgHeaderBase> InitHeader(uint8 nHeadType);

	void Reset();

	void OnReciveMsg();

	int32 GetPendingReciveDataLength();
	//void SetClientIndex(uint32 nClientIndex);
	int64_t GetLastReciveHeartbeatTime();
	void SetLastReciveHeartbeatTime(int64_t nLastTime);
	void SetHeartbeatTime(int64_t nTime);
	int64_t GetMsgDelayTime();
	
private:
	uint32 m_nClientIndex = -1;
	EMsgReadState m_nState = MRS_HeadType;
	TSharedPtr<SGMsgHeaderBase> m_pMsgheader;
	TSharedPtr<IoBuffer> m_pMsgBuff;
	int64_t m_nReciveHeartbeatTime = 0;
	int64_t m_nSendHeartbeatTime = 0;
	uint32 m_nMsgDelay = 0;

	uint32 m_nNextReciveDataLength = 1;

};