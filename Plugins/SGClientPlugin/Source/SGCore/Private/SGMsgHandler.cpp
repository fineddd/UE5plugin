
#include "SGMsgHandler.h"

SGMsgHandler*  SGMsgHandler::pHandler = nullptr;

SGMsgHandler* SGMsgHandler::GetInstance()
{
	if (pHandler != nullptr)
	{
		return pHandler;
	}
	pHandler = new SGMsgHandler();
	return pHandler;
}

void SGMsgHandler::UnRegMsgDelegate(TMsgID nMsgID)
{
	m_mapMsgDelegates.Remove(nMsgID);
}

void SGMsgHandler::OnRecvMsg(TMsgID nMsgID, uint8* pMsgData, uint32 nMsgLength)
{
	auto pDelegate = m_mapMsgDelegates.Find(nMsgID);
	if (pDelegate == nullptr)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString::Printf(TEXT("unknow msg %d !"), (int)nMsgID)
			);
		}
		return;
	}
	pDelegate->Execute(pMsgData, nMsgLength);
}
