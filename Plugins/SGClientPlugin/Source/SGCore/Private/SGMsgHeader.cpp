#include "SGMsgHeader.h"
#include "terse/utils/Endianness.h"

uint32 SGClientHeader::GetHeadLength()
{
	return 12;
}

uint32 SGClientHeader::GetMsgLength()
{
	return m_uiSize;
}

void SGClientHeader::DeCode(const uint8* data)
{
	uint16 nOffset = 0;

	uint32 nSize = 0;
	FMemory::Memcpy(&nSize, data + nOffset, sizeof(nSize));
	m_uiSize = ntoh(nSize);
	nOffset += sizeof(nSize);

	uint16 nMsgID = 0;
	FMemory::Memcpy(&nMsgID, data + nOffset, sizeof(nMsgID));
	m_nMsgID = ntoh(nMsgID);
	nOffset += sizeof(nMsgID);

	uint8 cSerial = 0;
	FMemory::Memcpy(&cSerial, data + nOffset, sizeof(cSerial));
	m_cSerial = ntoh(cSerial);
	nOffset += sizeof(cSerial);

	uint32 CrcCode = 0;
	FMemory::Memcpy(&CrcCode, data + nOffset, sizeof(CrcCode));
	mCrcCode = ntoh(CrcCode);
	nOffset += sizeof(CrcCode);
	return;
}


void SGClientHeader::EnCode(uint8* data)
{
	uint16 nOffset = 0;

	uint8 nType = hton((uint8)MHT_ClientToServer);
	FMemory::Memcpy(data + nOffset, &nType, sizeof(nType));
	nOffset += sizeof(nType);

	uint32 nSize = hton(m_uiSize);
	FMemory::Memcpy(data + nOffset, &nSize,  sizeof(nSize));
	nOffset += sizeof(nSize);

	uint16 nMsgID = hton(m_nMsgID);
	FMemory::Memcpy(data + nOffset, &nMsgID,  sizeof(nMsgID));
	nOffset += sizeof(nMsgID);

	uint8 cSerial = hton(m_cSerial);
	FMemory::Memcpy(data + nOffset, &cSerial, sizeof(cSerial));
	nOffset += sizeof(cSerial);

	uint32 CrcCode = hton(mCrcCode);
	FMemory::Memcpy(data + nOffset, &CrcCode,  sizeof(CrcCode));
	nOffset += sizeof(CrcCode);
	return;
}

uint16 SGClientHeader::GetMsgID()
{
	return m_nMsgID;
}

uint32 SGClientHeader::GetSerial()
{
	return m_cSerial;
}
uint8 SGClientHeader::GetHeadType()
{
	return MHT_ClientToServer;
}

void SGClientHeader::Reset()
{
	m_uiSize = 0;
	m_nMsgID = 0;
	m_cSerial = 0;
	mCrcCode = 0;
}


uint32 SGServerHeader::GetHeadLength()
{
	return 11;
}

uint32 SGServerHeader::GetMsgLength()
{
	return m_uiSize;
}

void SGServerHeader::DeCode(const uint8* data)
{
	uint16 nOffset = 0;

	uint32 nSize = 0;
	FMemory::Memcpy(&nSize, data + nOffset, sizeof(nSize));
	m_uiSize = ntoh(nSize);
	nOffset += sizeof(nSize);

	uint16 nMsgID = 0;
	FMemory::Memcpy(&nMsgID, data + nOffset, sizeof(nMsgID));
	m_nMsgID = ntoh(nMsgID);
	nOffset += sizeof(nMsgID);

	uint32 nMsgIndex = 0;
	FMemory::Memcpy(&nMsgIndex, data + nOffset, sizeof(nMsgIndex));
	m_nMsgIndex = ntoh(nMsgIndex);
	nOffset += sizeof(nMsgIndex);
	return;
}

void SGServerHeader::EnCode(uint8* data)
{
	uint16 nOffset = 0;

	uint8 nType = hton((uint8)MHT_ServerToClient);
	FMemory::Memcpy(data + nOffset, &nType, sizeof(nType));
	nOffset += sizeof(nType);

	uint32 nSize = hton(m_uiSize);
	FMemory::Memcpy(data + nOffset, &nSize, sizeof(nSize));
	nOffset += sizeof(nSize);

	uint16 nMsgID = hton(m_nMsgID);
	FMemory::Memcpy(data + nOffset, &nMsgID, sizeof(nMsgID));
	nOffset += sizeof(nMsgID);

	uint32 cSerial = hton(m_nMsgIndex);
	FMemory::Memcpy(data + nOffset, &cSerial, sizeof(cSerial));
	nOffset += sizeof(cSerial);

	return;
}

uint16 SGServerHeader::GetMsgID()
{
	return m_nMsgID;
}

uint32 SGServerHeader::GetSerial()
{
	return m_nMsgIndex;
}
uint8 SGServerHeader::GetHeadType()
{
	return MHT_ServerToClient;
}

void SGServerHeader::Reset()
{
	m_uiSize = 0;
	m_nMsgID = 0;
	m_nMsgIndex = 0;
}
