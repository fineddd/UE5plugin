// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SGLoginModule/Public/SGLoginWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSGLoginWidget() {}
// Cross Module References
	SGLOGINMODULE_API UClass* Z_Construct_UClass_USGLoginWidget();
	SGLOGINMODULE_API UClass* Z_Construct_UClass_USGLoginWidget_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_SGLoginModule();
// End Cross Module References
	DEFINE_FUNCTION(USGLoginWidget::execLoginButtonCliked)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->LoginButtonCliked();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USGLoginWidget::execMenuSetup)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->MenuSetup();
		P_NATIVE_END;
	}
	void USGLoginWidget::StaticRegisterNativesUSGLoginWidget()
	{
		UClass* Class = USGLoginWidget::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "LoginButtonCliked", &USGLoginWidget::execLoginButtonCliked },
			{ "MenuSetup", &USGLoginWidget::execMenuSetup },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_USGLoginWidget_LoginButtonCliked_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USGLoginWidget_LoginButtonCliked_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SGLoginWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USGLoginWidget_LoginButtonCliked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USGLoginWidget, nullptr, "LoginButtonCliked", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USGLoginWidget_LoginButtonCliked_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USGLoginWidget_LoginButtonCliked_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USGLoginWidget_LoginButtonCliked()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USGLoginWidget_LoginButtonCliked_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USGLoginWidget_MenuSetup_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USGLoginWidget_MenuSetup_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SGLoginWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USGLoginWidget_MenuSetup_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USGLoginWidget, nullptr, "MenuSetup", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USGLoginWidget_MenuSetup_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USGLoginWidget_MenuSetup_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USGLoginWidget_MenuSetup()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USGLoginWidget_MenuSetup_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USGLoginWidget);
	UClass* Z_Construct_UClass_USGLoginWidget_NoRegister()
	{
		return USGLoginWidget::StaticClass();
	}
	struct Z_Construct_UClass_USGLoginWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LoginButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LoginButton;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USGLoginWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_SGLoginModule,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_USGLoginWidget_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_USGLoginWidget_LoginButtonCliked, "LoginButtonCliked" }, // 3012342641
		{ &Z_Construct_UFunction_USGLoginWidget_MenuSetup, "MenuSetup" }, // 3679845150
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USGLoginWidget_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "SGLoginWidget.h" },
		{ "ModuleRelativePath", "Public/SGLoginWidget.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USGLoginWidget_Statics::NewProp_LoginButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/SGLoginWidget.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USGLoginWidget_Statics::NewProp_LoginButton = { "LoginButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(USGLoginWidget, LoginButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(Z_Construct_UClass_USGLoginWidget_Statics::NewProp_LoginButton_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USGLoginWidget_Statics::NewProp_LoginButton_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USGLoginWidget_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USGLoginWidget_Statics::NewProp_LoginButton,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USGLoginWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USGLoginWidget>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_USGLoginWidget_Statics::ClassParams = {
		&USGLoginWidget::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_USGLoginWidget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_USGLoginWidget_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(Z_Construct_UClass_USGLoginWidget_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USGLoginWidget_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USGLoginWidget()
	{
		if (!Z_Registration_Info_UClass_USGLoginWidget.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USGLoginWidget.OuterSingleton, Z_Construct_UClass_USGLoginWidget_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_USGLoginWidget.OuterSingleton;
	}
	template<> SGLOGINMODULE_API UClass* StaticClass<USGLoginWidget>()
	{
		return USGLoginWidget::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(USGLoginWidget);
	USGLoginWidget::~USGLoginWidget() {}
	struct Z_CompiledInDeferFile_FID_projects_sgclient_Plugins_SGClientPlugin_Source_SGLoginModule_Public_SGLoginWidget_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_sgclient_Plugins_SGClientPlugin_Source_SGLoginModule_Public_SGLoginWidget_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_USGLoginWidget, USGLoginWidget::StaticClass, TEXT("USGLoginWidget"), &Z_Registration_Info_UClass_USGLoginWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USGLoginWidget), 3457327167U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_sgclient_Plugins_SGClientPlugin_Source_SGLoginModule_Public_SGLoginWidget_h_3141603952(TEXT("/Script/SGLoginModule"),
		Z_CompiledInDeferFile_FID_projects_sgclient_Plugins_SGClientPlugin_Source_SGLoginModule_Public_SGLoginWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_projects_sgclient_Plugins_SGClientPlugin_Source_SGLoginModule_Public_SGLoginWidget_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
