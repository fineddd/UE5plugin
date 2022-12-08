// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SGServerListEntry.generated.h"

/**
 * 
 */
UCLASS()
class SGLOGINMODULE_API USGServerListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void ButtonServer1Cliked();
	UFUNCTION()
	void ButtonServer2Cliked();
	
protected:
	virtual bool Initialize();

	void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonServer1;
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonServer2;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ButtonServer1Text;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ButtonServer2Text;

	int m_nBigAreaID1 = 0;
	int m_nBigAreaID2 = 0;
	int m_nAreaID1 = 0;
	int m_nAreaID2 = 0;
};
