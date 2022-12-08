// Fill out your copyright notice in the Description page of Project Settings.


#include "SGServerListItem.h"


void USGServerListItem::SetServerItemData(int nDataIndex, int nBigAreaID, int nAreaID, const std::string& strServerName)
{
	if (nDataIndex == 0)
	{
		nBigAreaID1 = nBigAreaID;
		nAreaID1 = nAreaID;
		Server1Text= FString(UTF8_TO_TCHAR(strServerName.c_str()));
	}
	else
	{
		nBigAreaID2 = nBigAreaID;
		nAreaID2 = nAreaID;
		Server2Text = FString(UTF8_TO_TCHAR(strServerName.c_str()));
	}
}
