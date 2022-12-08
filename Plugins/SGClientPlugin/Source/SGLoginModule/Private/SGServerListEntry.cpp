// Fill out your copyright notice in the Description page of Project Settings.


#include "SGServerListEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "SGServerListItem.h"
#include "SGLoginProcess.h"

void USGServerListEntry::ButtonServer1Cliked()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Blue,
		FString::Printf(TEXT("Choose server %d!"), m_nAreaID1)
	);
	SGLoginProcess::Instance().ChoiceServer(m_nBigAreaID1, m_nAreaID1);
}

void USGServerListEntry::ButtonServer2Cliked()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Blue,
		FString::Printf(TEXT("Choose server %d!"), m_nAreaID2)
	);
	SGLoginProcess::Instance().ChoiceServer(m_nBigAreaID2, m_nAreaID2);
}

bool USGServerListEntry::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (ButtonServer1)
	{
		ButtonServer1->OnClicked.AddDynamic(this, &ThisClass::ButtonServer1Cliked);
	}
	if (ButtonServer2)
	{
		ButtonServer2->OnClicked.AddDynamic(this, &ThisClass::ButtonServer2Cliked);
	}
	return true;
}

void USGServerListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	auto pItem = static_cast<USGServerListItem*>(ListItemObject);
	if (pItem == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString(TEXT("item cast error !"))
		);
		return;
	}
	if (pItem->nAreaID1 > 0)
	{
		ButtonServer1->SetVisibility(ESlateVisibility::Visible);
		ButtonServer1Text->SetText(FText::FromString(pItem->Server1Text));
		m_nAreaID1 = pItem->nAreaID1;
		m_nBigAreaID1 = pItem->nBigAreaID1;
	}
	else
	{
		ButtonServer1->SetVisibility(ESlateVisibility::Hidden);
	}

	if (pItem->nAreaID2 > 0)
	{
		ButtonServer2->SetVisibility(ESlateVisibility::Visible);
		ButtonServer2Text->SetText(FText::FromString(pItem->Server2Text));
		m_nAreaID2 = pItem->nAreaID2;
		m_nBigAreaID2 = pItem->nBigAreaID2;
	}
	else
	{
		ButtonServer2->SetVisibility(ESlateVisibility::Hidden);
	}
}
