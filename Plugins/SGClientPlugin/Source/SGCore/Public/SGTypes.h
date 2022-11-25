#pragma once

//#include "CoreMinimal.h"
//#include "Engine.h"
#include "EngineGlobals.h"
//#include "EngineGlobals.h"
//#include "Delegates/DelegateCombinations.h"
//#include "Delegates/DelegateInstancesImpl.h"
#include "Containers/UnrealString.h"
//class MemoryStream;

typedef uint16 TMsgID;

DECLARE_DELEGATE_RetVal_TwoParams(int, MsgHandleDelegate, uint8*, uint32)
DECLARE_LOG_CATEGORY_EXTERN(SGLog, Log, All)

enum EMsgHeadType
{
	MHT_ClientToServer = 6,
	MHT_ServerToClient = 7,
};

enum EMsgReadState
{
	MRS_HeadType,
	MRS_Head,
	MRS_Body,
};