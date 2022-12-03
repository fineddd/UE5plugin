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


	void BeginDestroy() override;

protected:
	virtual bool Initialize();

private:
	//msg cb
	int OnEncryptoTypeRecive(uint32 nClientIndex, uint8* pData, uint32 nLength);
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* LoginButton;
	int m_nTcpClientIndex = -1;
};
