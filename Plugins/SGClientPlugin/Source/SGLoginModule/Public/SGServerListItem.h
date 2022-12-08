// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SGServerListItem.generated.h"

/**
 * 
 */
UCLASS()
class SGLOGINMODULE_API USGServerListItem : public UObject
{
	GENERATED_BODY()
	
public:
	void SetServerItemData(int nDataIndex, int nBigAreaID, int nAreaID, const std::string& strServerName);

	FString Server1Text;
	FString Server2Text;
	int nBigAreaID1 = 0;
	int nBigAreaID2 = 0;
	int nAreaID1 = 0;
	int nAreaID2 = 0;
};
