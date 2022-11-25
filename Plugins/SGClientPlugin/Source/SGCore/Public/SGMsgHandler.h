#pragma once
#include "SGTypes.h"
//#include "MemoryStream.h"

class SGCORE_API SGMsgHandler
{
public:
	virtual ~SGMsgHandler() {};

	static SGMsgHandler* GetInstance();

	template <typename UserClass>
	bool RegMsgDelegate(TMsgID nMsgID, UserClass* pClass, int (UserClass::* UserDelegate)(uint8*, uint32 ) );

	void UnRegMsgDelegate(TMsgID nMsgID);

	void OnRecvMsg(TMsgID nMsgID, uint8* pMsgData, uint32 nMsgLength);
private:
	SGMsgHandler() {};

private:
	static SGMsgHandler* pHandler;

private:
	TMap<TMsgID, MsgHandleDelegate> m_mapMsgDelegates;
};

template <typename UserClass>
bool SGMsgHandler::RegMsgDelegate(TMsgID nMsgID, UserClass* pClass, int (UserClass::* UserDelegate)( uint8*, uint32 ))
{
	auto pDelegate = m_mapMsgDelegates.Find(nMsgID);
	if (pDelegate != nullptr)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString::Printf(TEXT("repeated reg msg handle %d !"), (int)nMsgID)
			);
		}
	}
	MsgHandleDelegate xDelegate;
	xDelegate.BindRaw(pClass, UserDelegate);
	m_mapMsgDelegates[nMsgID] = xDelegate;
	//m_mapMsgDelegates.emplace(nMsgID, xDelegate);
	return true;
}
