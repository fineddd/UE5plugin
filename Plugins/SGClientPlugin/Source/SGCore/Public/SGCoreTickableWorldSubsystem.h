// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SGCoreTickableWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SGCORE_API USGCoreTickableWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:
	void Tick(float DeltaTime) override;


	TStatId GetStatId() const override;

};
