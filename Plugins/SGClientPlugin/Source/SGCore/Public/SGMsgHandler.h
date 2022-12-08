#pragma once
#include "SGTypes.h"
//#include "MemoryStream.h"
#include <unordered_map>



class SGCORE_API SGMsgHandler
{
public:
    virtual ~SGMsgHandler() {};

    static SGMsgHandler* GetInstance();

    template <typename UserClass>
    bool RegMsgUObjectDelegate(TMsgID nMsgID, UserClass* pClass, int (UserClass::* UserDelegate)(uint32, uint8*, uint32));
	
    template <typename UserClass>
	bool RegMsgRowDelegate(TMsgID nMsgID, UserClass* pClass, int (UserClass::* UserDelegate)(uint32, uint8*, uint32));

    void UnRegMsgDelegate(TMsgID nMsgID);

    void OnRecvMsg(TMsgID nMsgID, uint32 nClientIndex, uint8* pMsgData, uint32 nMsgLength);
private:
    SGMsgHandler() {};

private:
    static SGMsgHandler* pHandler;

private:
    TMap<int, MsgHandleDelegate> m_mapMsgDelegates;   //msgid, Delegate
};

template <typename UserClass>
bool SGMsgHandler::RegMsgUObjectDelegate(TMsgID nMsgID, UserClass* pClass, int (UserClass::* UserDelegate)(uint32, uint8*, uint32))
{
	auto pMsgDelegates = m_mapMsgDelegates.Find(nMsgID);
	if (pMsgDelegates != nullptr)
	{
		//UE_LOG(SGLog, Error, TEXT("repeated msg delegate msgid: %d"), nMsgID);
		return false;
	}
	MsgHandleDelegate xDelegate;
    xDelegate.BindUObject(pClass, UserDelegate);

    m_mapMsgDelegates.Add(nMsgID, xDelegate);
    return true;
}
template <typename UserClass>
bool SGMsgHandler::RegMsgRowDelegate(TMsgID nMsgID, UserClass* pClass, int (UserClass::* UserDelegate)(uint32, uint8*, uint32))
{
	auto pMsgDelegates = m_mapMsgDelegates.Find(nMsgID);
	if (pMsgDelegates != nullptr)
	{
		//UE_LOG(SGLog, Error, TEXT("repeated msg delegate msgid: %d"), nMsgID);
		return false;
	}
	MsgHandleDelegate xDelegate;
	xDelegate.BindRaw(pClass, UserDelegate);

	m_mapMsgDelegates.Add(nMsgID, xDelegate);
	return true;
}
