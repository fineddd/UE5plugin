#pragma once

//#include "CoreMinimal.h"
//#include "Engine.h"
#include "EngineGlobals.h"
//#include "EngineGlobals.h"
//#include "Delegates/DelegateCombinations.h"
//#include "Delegates/DelegateInstancesImpl.h"
#include "Containers/UnrealString.h"
//class MemoryStream;
#include "Logging/LogMacros.h"

typedef uint16 TMsgID;

DECLARE_DELEGATE_RetVal_ThreeParams(int, MsgHandleDelegate, uint32, uint8*, uint32)
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

enum EEncryptionType
{
    ENCRYPTION_BASE64 = 1,
    ENCRYPTION_AES = 2,
    ENCRYPTION_BLOWFISH = 3,
    ENCRYPTION_SIMPLE = 4,
};