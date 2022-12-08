// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGLoginWidget.generated.h"

namespace SGMsg
{
	class S2SServerInfoReportList;
}
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

	UFUNCTION()
	void QuitServerListButtonCliked();

	void SetAreaChoiceMenu(const SGMsg::S2SServerInfoReportList& xServerInfoList);
	//void SetLoadingMenu();
	//void SetLoadingProgress(float percent);

	void BeforeDestroy();
protected:
	virtual bool Initialize();

private:

private:
	//login
	UPROPERTY(meta = (BindWidget))
	class UButton* LoginButton;
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* EditAreaBox;
	UPROPERTY(meta = (BindWidget))
	class UImage* LoginBgImage;
	UPROPERTY(meta = (BindWidget))
	class UEditableText* ConfigAddrInputText;
	UPROPERTY(meta = (BindWidget))
	class UEditableText* PlayerIDInputText;
	//server list
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanelServerList;
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonQuitServerList;
	UPROPERTY(meta = (BindWidget))
	class UListView* ListViewServer;

	//UPROPERTY(meta = (BindWidget))
	//class UCanvasPanel* PanelLoading;
	//UPROPERTY(meta = (BindWidget))
	//class UProgressBar* ProgressBarLoading;
};
