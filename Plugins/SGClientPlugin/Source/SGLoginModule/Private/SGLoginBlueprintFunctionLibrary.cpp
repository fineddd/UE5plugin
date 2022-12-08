// Fill out your copyright notice in the Description page of Project Settings.


#include "SGLoginBlueprintFunctionLibrary.h"

#include "SGLoginProcess.h"

void USGLoginBlueprintFunctionLibrary::LoginLevelInit()
{
	SGLoginProcess::Instance().StartLogin();
}
