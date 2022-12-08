// Fill out your copyright notice in the Description page of Project Settings.

#include "SGLoginWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/Image.h"
#include "Components/EditableText.h"
#include "Components/ListView.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"

#include "SGLoginProcess.h"

#include "SGMsgLogin.pb.h"

#include "SGServerListItem.h"
#include "SGDefine.pb.h"

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

    CanvasPanelServerList->SetVisibility(ESlateVisibility::Hidden);
    //PanelLoading->SetVisibility(ESlateVisibility::Hidden);
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

    SGLoginProcess::Instance().OnLoginBegin(PlayerIDInputText->GetText().ToString(), ConfigAddrInputText->GetText().ToString());
    //EditAreaBox->SetVisibility(ESlateVisibility::Hidden);
}
void USGLoginWidget::QuitServerListButtonCliked()
{
    CanvasPanelServerList->SetVisibility(ESlateVisibility::Hidden);
    ListViewServer->ClearListItems();
    EditAreaBox->SetVisibility(ESlateVisibility::Visible);
    SGLoginProcess::Instance().ChoiceServerCancel();
}
void USGLoginWidget::SetAreaChoiceMenu(const SGMsg::S2SServerInfoReportList& xServerInfoList)
{
    EditAreaBox->SetVisibility(ESlateVisibility::Hidden);
	int nServerIndex = 0;

	ListViewServer->ClearListItems();
	for (int i = 0; i < xServerInfoList.server_list_size(); ++i)
	{
		auto& xServerInfo = xServerInfoList.server_list(i);
		if (xServerInfo.server_state() == SGDefine::EST_MAINTEN)
		{
			continue;
		}
		int nButtonIndex = nServerIndex % 2;
		if (nButtonIndex == 0)
		{
            auto pItem = NewObject<USGServerListItem>();
			ListViewServer->AddItem(pItem);
		}
		int itemsize = ListViewServer->GetNumItems();
		auto pWidget = static_cast<USGServerListItem*>(ListViewServer->GetItemAt(itemsize - 1));
		pWidget->SetServerItemData(nButtonIndex, xServerInfo.big_area(), xServerInfo.area(), xServerInfo.area_name());
		++nServerIndex;
	}
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Black,
		FString::Printf(TEXT("server size %d !"), nServerIndex)
	);
	//ListViewServer->RequestRefresh();
    CanvasPanelServerList->SetVisibility(ESlateVisibility::Visible);
	return;
}
//void USGLoginWidget::SetLoadingMenu()
//{
//    CanvasPanelServerList->SetVisibility(ESlateVisibility::Hidden);
//    EditAreaBox->SetVisibility(ESlateVisibility::Hidden);
//    LoginBgImage->SetVisibility(ESlateVisibility::Hidden);
//
//    ProgressBarLoading->SetPercent(0.1);
//    PanelLoading->SetVisibility(ESlateVisibility::Visible);
//}
//void USGLoginWidget::SetLoadingProgress(float percent)
//{
//    ProgressBarLoading->SetPercent(percent);
//}
void USGLoginWidget::BeforeDestroy()
{
    RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
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
	if (ButtonQuitServerList)
	{
        ButtonQuitServerList->OnClicked.AddDynamic(this, &ThisClass::QuitServerListButtonCliked);
	}
    return true;
}
