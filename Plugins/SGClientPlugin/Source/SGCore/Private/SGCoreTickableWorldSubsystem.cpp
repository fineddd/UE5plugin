// Fill out your copyright notice in the Description page of Project Settings.


#include "SGCoreTickableWorldSubsystem.h"

#include "SGCoreApp.h"

void USGCoreTickableWorldSubsystem::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);
	SGCoreApp::GetInstance()->Process(DeltaTime);
}

TStatId USGCoreTickableWorldSubsystem::GetStatId() const
{
	return TStatId();
}
