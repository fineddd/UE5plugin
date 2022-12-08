// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SGLoginBlueprintFunctionLibrary.generated.h"


class USGLoginWidget;
/**
 * 
 */
UCLASS()
class SGLOGINMODULE_API USGLoginBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void LoginLevelInit();
};
