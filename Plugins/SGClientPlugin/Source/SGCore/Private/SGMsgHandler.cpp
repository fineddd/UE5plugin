
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

void SGMsgHandler::OnRecvMsg(TMsgID nMsgID, uint32 nClientIndex, uint8* pMsgData, uint32 nMsgLength)
{
    auto pMsgDelegates = m_mapMsgDelegates.Find(nMsgID);
    if (pMsgDelegates == nullptr)
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
    pMsgDelegates->Execute(nClientIndex, pMsgData, nMsgLength);
}
