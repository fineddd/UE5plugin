#pragma once

//#include "SGTypes.h"
#include "SGSingleton.h"
#include "CoreMinimal.h"
#include "SGLoginWidget.h"
#include "SGMsgBase.pb.h"

enum ELoginStep
{
	LS_LoginWindow,
	LS_LoginConfig,
	LS_AreaChoice,
	LS_GateServer,
	//LS_GateTokenVerify,
	//LS_EnterGame,
};

class SGLoginProcess : public Singleton<SGLoginProcess>
{
public:
	SGLoginProcess()
	{
		Init();
	}

	virtual ~SGLoginProcess();

	//static SGLoginProcess* GetInstance();

	void Init();
	void Reset();

	void StartLogin();
	void OnLoginBegin(const FString& strPlayerAccount, const FString& strServerAddr);

	void ChoiceServerCancel();
	void ChoiceServer(int nBigAreaID, int nAreaID);
	//msg cb
	int OnEncryptoTypeRecive(uint32 nClientIndex, uint8* pData, uint32 nLength);
	int OnRSPConfigLoginResult(uint32 nClientIndex, uint8* pData, uint32 nLength);
	int OnAckQueryGate(uint32 nClientIndex, uint8* pData, uint32 nLength);
	int OnRspLoginResult(uint32 nClientIndex, uint8* pData, uint32 nLength);
	int OnRspCharList(uint32 nClientIndex, uint8* pData, uint32 nLength);
	int OnRspCreateChar(uint32 nClientIndex, uint8* pData, uint32 nLength);
	int OnRspEnterGame(uint32 nClientIndex, uint8* pData, uint32 nLength);

	void FakeFinishLoading();
private:
	void OnConfigEncryptoInfoRecive();
	void OnGateEncryptoInfoRecive();

	void ResetToServerListState();

private:
	//static SGLoginProcess* pLoginProcessInstance;
private:
	ELoginStep m_eStep = LS_LoginWindow;
	int m_nTcpClientIndex = -1;

	//TSubclassOf<UUserWidget> m_pCurWidgetClass;
	USGLoginWidget* m_pLoginWidget = nullptr;

	std::string m_strPlayerAccount;
	FString m_strConfigServerIP;
	int m_nConfigServerPort;
	//
	SGMsg::GUID m_xClientID;
	SGMsg::GUID m_xGateEncryptoID;
	SGMsg::GUID m_xConfigClientID;
	int m_nBigAreaID = 0;
	int m_nAreaID = 0;

	FString m_strGateServerIP;
	int m_nGateServerPort;
	std::string m_strToken;
	//role data
	SGMsg::GUID m_xLastRoleID;
	int m_nLastGameServerID = 0;

	SGMsg::GUID m_xRoleID;

	//float fFakeLoginProgress = 0.3;
};
