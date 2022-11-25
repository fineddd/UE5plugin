// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SGCore/Public/SGCoreTickableWorldSubsystem.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSGCoreTickableWorldSubsystem() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UTickableWorldSubsystem();
	SGCORE_API UClass* Z_Construct_UClass_USGCoreTickableWorldSubsystem();
	SGCORE_API UClass* Z_Construct_UClass_USGCoreTickableWorldSubsystem_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SGCore();
// End Cross Module References
	void USGCoreTickableWorldSubsystem::StaticRegisterNativesUSGCoreTickableWorldSubsystem()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USGCoreTickableWorldSubsystem);
	UClass* Z_Construct_UClass_USGCoreTickableWorldSubsystem_NoRegister()
	{
		return USGCoreTickableWorldSubsystem::StaticClass();
	}
	struct Z_Construct_UClass_USGCoreTickableWorldSubsystem_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USGCoreTickableWorldSubsystem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UTickableWorldSubsystem,
		(UObject* (*)())Z_Construct_UPackage__Script_SGCore,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USGCoreTickableWorldSubsystem_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "SGCoreTickableWorldSubsystem.h" },
		{ "ModuleRelativePath", "Public/SGCoreTickableWorldSubsystem.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USGCoreTickableWorldSubsystem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USGCoreTickableWorldSubsystem>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_USGCoreTickableWorldSubsystem_Statics::ClassParams = {
		&USGCoreTickableWorldSubsystem::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_USGCoreTickableWorldSubsystem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USGCoreTickableWorldSubsystem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USGCoreTickableWorldSubsystem()
	{
		if (!Z_Registration_Info_UClass_USGCoreTickableWorldSubsystem.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USGCoreTickableWorldSubsystem.OuterSingleton, Z_Construct_UClass_USGCoreTickableWorldSubsystem_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_USGCoreTickableWorldSubsystem.OuterSingleton;
	}
	template<> SGCORE_API UClass* StaticClass<USGCoreTickableWorldSubsystem>()
	{
		return USGCoreTickableWorldSubsystem::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(USGCoreTickableWorldSubsystem);
	USGCoreTickableWorldSubsystem::~USGCoreTickableWorldSubsystem() {}
	struct Z_CompiledInDeferFile_FID_projects_sgclient_Plugins_SGClientPlugin_Source_SGCore_Public_SGCoreTickableWorldSubsystem_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_sgclient_Plugins_SGClientPlugin_Source_SGCore_Public_SGCoreTickableWorldSubsystem_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_USGCoreTickableWorldSubsystem, USGCoreTickableWorldSubsystem::StaticClass, TEXT("USGCoreTickableWorldSubsystem"), &Z_Registration_Info_UClass_USGCoreTickableWorldSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USGCoreTickableWorldSubsystem), 686822604U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_sgclient_Plugins_SGClientPlugin_Source_SGCore_Public_SGCoreTickableWorldSubsystem_h_897239024(TEXT("/Script/SGCore"),
		Z_CompiledInDeferFile_FID_projects_sgclient_Plugins_SGClientPlugin_Source_SGCore_Public_SGCoreTickableWorldSubsystem_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_projects_sgclient_Plugins_SGClientPlugin_Source_SGCore_Public_SGCoreTickableWorldSubsystem_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
