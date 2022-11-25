#pragma once
#include "SGTypes.h"

class SGCORE_API SGMsgHeaderBase
{
public:
	virtual uint32 GetHeadLength() = 0;
	virtual uint32 GetMsgLength() = 0;
	//输入参数类型后面确定
	virtual void DeCode(const uint8* data) = 0;
	virtual void EnCode(uint8* data) = 0;

	virtual uint16 GetMsgID() = 0;
	virtual uint32 GetSerial() = 0;

	virtual uint8 GetHeadType() = 0;
	virtual void Reset() = 0;
};

class SGCORE_API SGClientHeader : public SGMsgHeaderBase
{
public:
	SGClientHeader()
	{
	}
	virtual ~SGClientHeader()
	{
	}

	uint32 GetHeadLength() override;
	uint32 GetMsgLength() override;
	void DeCode(const uint8* data) override;
	void EnCode(uint8* data) override;
	uint16 GetMsgID() override;
	uint32 GetSerial() override;
	uint8 GetHeadType() override;

	void Reset() override;


	uint32 m_uiSize = 0;
	uint16 m_nMsgID = 0;              // 枚举见MG_PTOTOCOL_TYPES
	uint8  m_cSerial = 0;            // 枚举见int,如果是client发往网关，则为序列号；
	uint32 mCrcCode = 0;              //如果是client发送过来则是CRC32校验码；
};


class SGCORE_API SGServerHeader : public SGMsgHeaderBase
{
public:
	SGServerHeader()
	{
	}
	virtual ~SGServerHeader()
	{
	}

	uint32 GetHeadLength() override;
	uint32 GetMsgLength() override;
	void DeCode(const uint8* data) override;
	void EnCode(uint8* data) override;
	uint16 GetMsgID() override;
	uint32 GetSerial() override;
	uint8 GetHeadType() override;

	void Reset() override;


	uint32 m_uiSize = 0;
	uint16 m_nMsgID = 0;              // 枚举见MG_PTOTOCOL_TYPES
	uint32 m_nMsgIndex = 0;              //如果是client发送过来则是index；
};