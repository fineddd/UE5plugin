// Fill out your copyright notice in the Description page of Project Settings.

#include "SGLoginWidget.h"
#include "Components/Button.h"
#include "SGTCPNetwork.h"
#include "SGCoreApp.h"

void USGLoginWidget::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}
}

void USGLoginWidget::LoginButtonCliked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Blue,
			FString(TEXT("Login Button cliked"))
		);
	}
	auto pNetWork = SGCoreApp::GetInstance()->GetTcpNetwork();

	FString addr = TEXT("10.26.12.232");
	pNetWork->ConnectTo(addr, 39001, 1);
}

bool USGLoginWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (LoginButton)
	{
		LoginButton->OnClicked.AddDynamic(this, &ThisClass::LoginButtonCliked);
	}
	return true;
}
