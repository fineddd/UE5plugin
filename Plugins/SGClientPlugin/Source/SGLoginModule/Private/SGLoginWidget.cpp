// Fill out your copyright notice in the Description page of Project Settings.

#include "SGLoginWidget.h"
#include "Components/Button.h"
#include "SGTCPClient.h"
#include "SGCoreApp.h"

#include "MsgID.pb.h"
#include "SGMsgHandler.h"
#include "SGMsgBase.pb.h"


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
    if (m_nTcpClientIndex < 0)
    {
        m_nTcpClientIndex = SGCoreApp::GetInstance()->NewTcpClient();
    }
    auto pNetWork = SGCoreApp::GetInstance()->GetTcpClient(m_nTcpClientIndex);

    FString addr = TEXT("10.26.12.232");
    pNetWork->ConnectTo(addr, 39001);
}

void USGLoginWidget::BeginDestroy()
{
	Super::BeginDestroy();

    SGMsgHandler::GetInstance()->UnRegMsgDelegate(MsgID::MSG_C2S_REQ_ACCOUNT_LOGIN);
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
    SGMsgHandler::GetInstance()->RegMsgDelegate(MsgID::MSG_C2S_REQ_ACCOUNT_LOGIN, this, &USGLoginWidget::OnEncryptoTypeRecive);
    return true;
}

int USGLoginWidget::OnEncryptoTypeRecive(uint32 nClientIndex, uint8* pData, uint32 nLength)
{
	SGMsg::GUID xMsg;

	if (!xMsg.ParseFromArray(pData, nLength))
	{
		//UE_LOG(SGLog, Error, TEXT("parse msg error,"), nLength);
		return 1;
	}
    auto pNetWork = SGCoreApp::GetInstance()->GetTcpClient(nClientIndex);
	if (xMsg.head() != 0 && xMsg.data() != 0)
	{
        pNetWork->SetCrypto(true);
	}
	else
	{
        pNetWork->SetCrypto(false);
	}
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Red,
		FString(TEXT("OnEncryptoTypeRecive!"))
	);
	return 0;
}