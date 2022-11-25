// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSGCore_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_SGCore;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_SGCore()
	{
		if (!Z_Registration_Info_UPackage__Script_SGCore.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/SGCore",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x078A84EC,
				0xBB185200,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_SGCore.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_SGCore.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_SGCore(Z_Construct_UPackage__Script_SGCore, TEXT("/Script/SGCore"), Z_Registration_Info_UPackage__Script_SGCore, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x078A84EC, 0xBB185200));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
