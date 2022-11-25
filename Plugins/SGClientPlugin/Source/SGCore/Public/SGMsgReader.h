#pragma once

#include "SGTypes.h"
#include "IOBuffer.h"
#include "SGMsgHeader.h"

class SGCORE_API SGMsgReader
{
public:
	SGMsgReader() {
		m_pMsgBuff = MakeShared<IoBuffer>(1024*1024);
	};
	virtual ~SGMsgReader() {};

	bool Process(uint8* pData, uint32 nLength);

	TSharedPtr<SGMsgHeaderBase> InitHeader(uint8 nHeadType);

	void Reset();

	void OnReciveMsg();

private:

	EMsgReadState m_nState = MRS_HeadType;
	TSharedPtr<SGMsgHeaderBase> m_pMsgheader;
	TSharedPtr<IoBuffer> m_pMsgBuff;
};