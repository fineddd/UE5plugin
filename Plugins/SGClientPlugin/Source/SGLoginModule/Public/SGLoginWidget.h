// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGLoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class SGLOGINMODULE_API USGLoginWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup();

	UFUNCTION()
	void LoginButtonCliked();

protected:
	virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* LoginButton;
};
