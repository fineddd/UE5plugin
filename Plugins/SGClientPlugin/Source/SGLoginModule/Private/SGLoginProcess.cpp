#include "SGLoginProcess.h"

#include "SGTCPClient.h"
#include "SGCoreApp.h"

#include "MsgID.pb.h"
#include "SGMsgHandler.h"
#include "SGMsgLogin.pb.h"

#include "Blueprint/UserWidget.h"
#include "Engine/World.h"

//#include "Engine/Engine.h"

//SGLoginProcess* SGLoginProcess::pLoginProcessInstance = nullptr;

SGLoginProcess::~SGLoginProcess()
{
	SGMsgHandler::GetInstance()->UnRegMsgDelegate(MsgID::MSG_C2S_REQ_ACCOUNT_LOGIN);
	SGMsgHandler::GetInstance()->UnRegMsgDelegate(MsgID::MSG_S2C_RSP_CONFIG_LOGIN_RESULT);
	SGMsgHandler::GetInstance()->UnRegMsgDelegate(MsgID::MSG_S2C_RSP_GATE_SERVER_INFO);
	SGMsgHandler::GetInstance()->UnRegMsgDelegate(MsgID::MSG_S2C_RSP_ACCOUNT_LOGIN);
	SGMsgHandler::GetInstance()->UnRegMsgDelegate(MsgID::MSG_S2C_RSP_CHAR_LIST);
	SGMsgHandler::GetInstance()->UnRegMsgDelegate(MsgID::MSG_S2C_RSP_CREATE_CHAR);
	SGMsgHandler::GetInstance()->UnRegMsgDelegate(MsgID::MSG_S2C_RSP_ENTER_GAMESERVER);
}
//SGLoginProcess* SGLoginProcess::GetInstance()
//{
//	if (pLoginProcessInstance == nullptr)
//	{
//		pLoginProcessInstance = new SGLoginProcess();
//	}
//	return pLoginProcessInstance;
//}
void SGLoginProcess::Init()
{
	//SGCoreApp::GetInstance()->RegFakeLoadingFinishDelegate(this, &SGLoginProcess::FakeFinishLoading);

	SGMsgHandler::GetInstance()->RegMsgRowDelegate(MsgID::MSG_C2S_REQ_ACCOUNT_LOGIN, this, &SGLoginProcess::OnEncryptoTypeRecive);
	SGMsgHandler::GetInstance()->RegMsgRowDelegate(MsgID::MSG_S2C_RSP_CONFIG_LOGIN_RESULT, this, &SGLoginProcess::OnRSPConfigLoginResult);
	SGMsgHandler::GetInstance()->RegMsgRowDelegate(MsgID::MSG_S2C_RSP_GATE_SERVER_INFO, this, &SGLoginProcess::OnAckQueryGate);
	SGMsgHandler::GetInstance()->RegMsgRowDelegate(MsgID::MSG_S2C_RSP_ACCOUNT_LOGIN, this, &SGLoginProcess::OnRspLoginResult);
	SGMsgHandler::GetInstance()->RegMsgRowDelegate(MsgID::MSG_S2C_RSP_CHAR_LIST, this, &SGLoginProcess::OnRspCharList);
	SGMsgHandler::GetInstance()->RegMsgRowDelegate(MsgID::MSG_S2C_RSP_CREATE_CHAR, this, &SGLoginProcess::OnRspCreateChar);
	SGMsgHandler::GetInstance()->RegMsgRowDelegate(MsgID::MSG_S2C_RSP_ENTER_GAMESERVER, this, &SGLoginProcess::OnRspEnterGame);
}
void SGLoginProcess::Reset()
{
	m_eStep = LS_LoginWindow;
	if (m_pLoginWidget != nullptr)
	{
		//m_pLoginWidget->RemoveFromViewport();
		m_pLoginWidget = nullptr;
	}
	m_xGateEncryptoID.Clear();
	m_nBigAreaID = 0;
	m_nAreaID = 0;
}
void SGLoginProcess::StartLogin()
{
	Reset();
	m_eStep = LS_LoginWindow;
	FString MenuPath = "/SGClientPlugin/WBP_Menu.WBP_Menu_C";
	UClass* MenuWidget = LoadClass<USGLoginWidget>(nullptr, *MenuPath);
	if (MenuWidget == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString(TEXT("load WBP_Menu error!"))
		);
		return;
	}
	m_pLoginWidget = CreateWidget<USGLoginWidget>(GWorld->GetWorld(), MenuWidget);
	m_pLoginWidget->MenuSetup();
}
void SGLoginProcess::OnLoginBegin(const FString& strPlayerAccount, const FString& strServerAddr)
{
	if (m_nTcpClientIndex < 0)
	{
		m_nTcpClientIndex = SGCoreApp::GetInstance()->NewTcpClient();
	}
	m_strPlayerAccount = TCHAR_TO_UTF8(*strPlayerAccount);

	FString strIP;
	FString strPort;
	if (!strServerAddr.Split(":", &strIP, &strPort))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString(TEXT("server addr format error!"))
		);
		return;
	}
	auto nPort = FCString::Atoi(*strPort);
	m_strConfigServerIP = strIP;
	m_nConfigServerPort = nPort;

	auto pNetWork = SGCoreApp::GetInstance()->GetTcpClient(m_nTcpClientIndex);
	if (pNetWork == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString(TEXT("net client null !"))
		);
		return;
	}
	
	pNetWork->ConnectTo(m_strConfigServerIP, m_nConfigServerPort);
}
void SGLoginProcess::ChoiceServerCancel()
{
	m_eStep = LS_LoginWindow;
	SGCoreApp::GetInstance()->CloseTcpClient(m_nTcpClientIndex);
	m_nTcpClientIndex = -1;
}
void SGLoginProcess::ChoiceServer(int nBigAreaID, int nAreaID)
{
	if (m_eStep != LS_AreaChoice)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("ChoiceServer login state error %d !"), m_eStep)
		);
		return;
	}
	SGMsg::C2SReqGateServerInfo xMsg;
	xMsg.set_client_version("5.3.3.0");

	xMsg.set_big_area_id(nBigAreaID);
	xMsg.set_area_id(nAreaID);

	m_nBigAreaID = nBigAreaID;
	m_nAreaID = nAreaID;

	SGCoreApp::GetInstance()->SendMsg(MsgID::MSG_C2S_REQ_GATE_SERVER_INFO, xMsg);
}
int SGLoginProcess::OnEncryptoTypeRecive(uint32 nClientIndex, uint8* pData, uint32 nLength)
{
	if (m_eStep != LS_LoginWindow && m_eStep != LS_GateServer)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("login state error %d !"), m_eStep)
		);
		return 1;
	}
	
	if (m_eStep == LS_LoginWindow)
	{
		if (!m_xConfigClientID.ParseFromArray(pData, nLength))
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString::Printf(TEXT("parse EncryptoTypeRecive error %d !"), m_eStep)
			);
			return 1;
		}
		OnConfigEncryptoInfoRecive();
	}
	else
	{
		if (!m_xGateEncryptoID.ParseFromArray(pData, nLength))
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString::Printf(TEXT("parse EncryptoTypeRecive error %d !"), m_eStep)
			);
			return 1;
		}
		OnGateEncryptoInfoRecive();
	}
	return 0;
}
int SGLoginProcess::OnRSPConfigLoginResult(uint32 nClientIndex, uint8* pData, uint32 nLength)
{
	if (m_eStep != LS_LoginConfig)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("login state error %d !"), m_eStep)
		);
		return 1;
	}
	SGMsg::S2CRspConfigLoginResult xReceivedMsg;
	if (!xReceivedMsg.ParseFromArray(pData, nLength))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("parse RSPConfigLoginResult error %d !"), m_eStep)
		);
		return 1;
	}
	if (xReceivedMsg.success() == false)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("unknow login error %d !"), m_eStep)
		);
		return 1;
	}
	m_eStep = LS_AreaChoice;
	m_pLoginWidget->SetAreaChoiceMenu(xReceivedMsg.server_list());
	return 0;
}
int SGLoginProcess::OnAckQueryGate(uint32 nClientIndex, uint8* pData, uint32 nLength)
{
	SGMsg::S2CRspGateServerInfo xMsg;
	if (!xMsg.ParseFromArray(pData, nLength))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("parse S2CRspGateServerInfo error %d !"), nClientIndex)
		);
		return 1;
	}
	m_strGateServerIP = FString(xMsg.gate_info().gate_ip().c_str());
	m_nGateServerPort = xMsg.gate_info().gate_port();
	m_strToken = xMsg.token();

	auto pNetWork = SGCoreApp::GetInstance()->GetTcpClient(nClientIndex);
	if (pNetWork == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString(TEXT("net client null !"))
		);
		return 1;
	}

	if (!pNetWork->ConnectTo(m_strGateServerIP, m_nGateServerPort))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("connect to gate error %s:%d !"), *m_strGateServerIP, m_nGateServerPort)
		);
		return 1;
	}
	m_eStep = LS_GateServer;
	return 0;
}
int SGLoginProcess::OnRspLoginResult(uint32 nClientIndex, uint8* pData, uint32 nLength)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Blue,
		FString(TEXT("OnRspLoginResult!"))
	);
	SGMsg::S2CRspAccountLogin xReceivedMsg;
	if (!xReceivedMsg.ParseFromArray(pData, nLength))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("parse S2CRspAccountLogin error %d !"), nClientIndex)
		);
		return 1;
	}
	if (xReceivedMsg.result() != SGMsg::S2CRspAccountLogin_LoginRet_LOGIN_SUCEESS)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("Gate Login Failed, Restart the client %d !"), xReceivedMsg.result())
		);
		ResetToServerListState();
		return 1;
	}
	m_xClientID = xReceivedMsg.client_id();
	m_xLastRoleID = xReceivedMsg.cur_role_id();
	m_nLastGameServerID = xReceivedMsg.cur_game_id();

	SGMsg::C2SReqCharList xMsg;
	xMsg.set_account(m_strPlayerAccount);
	SGCoreApp::GetInstance()->SendMsg(MsgID::MSG_C2S_REQ_CHAR_LIST, xMsg);
	return 0;
}
int SGLoginProcess::OnRspCharList(uint32 nClientIndex, uint8* pData, uint32 nLength)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Blue,
		FString(TEXT("OnRspCharList !"))
	);
	SGMsg::S2CRspCharList xReceivedMsg;
	if (!xReceivedMsg.ParseFromArray(pData, nLength))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("parse S2CRspAccountLogin error %d !"), nClientIndex)
		);
		return 1;
	}
	if (xReceivedMsg.char_list_size() > 0)
	{
		SGMsg::C2SReqEnterGameServer xMsg;
		xMsg.set_serverid(0);
		*xMsg.mutable_role_id() = xReceivedMsg.char_list(0).base_data().u_uid();
		SGCoreApp::GetInstance()->SendMsg(MsgID::MSG_C2S_REQ_ENTER_GAMESERVER, xMsg);
	}
	else
	{
		SGMsg::C2SReqCreateChar xMsg;
		xMsg.set_account(m_strPlayerAccount);
		xMsg.set_career(1);
		xMsg.set_sex(1);
		// 5 + 6 + 1 + 5 = 16
		std::string strRoleName = std::string("UEClient_") + m_strPlayerAccount.substr(0, 6) + "_1";
		xMsg.set_charname(strRoleName);

		SGCoreApp::GetInstance()->SendMsg(MsgID::MSG_C2S_REQ_CREATE_CHAR, xMsg);
	}
	return 0;
}
int SGLoginProcess::OnRspCreateChar(uint32 nClientIndex, uint8* pData, uint32 nLength)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Blue,
		FString(TEXT("OnRspCreateChar !"))
	);
	SGMsg::S2CRspCreateChar xReceivedMsg;
	if (!xReceivedMsg.ParseFromArray(pData, nLength))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("parse S2CRspAccountLogin error %d !"), nClientIndex)
		);
		return 1;
	}
	if (!xReceivedMsg.success())
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("create role error %d !"), nClientIndex)
		);
		return 1;
	}
	SGMsg::C2SReqCharList xMsg;
	xMsg.set_account(m_strPlayerAccount);
	SGCoreApp::GetInstance()->SendMsg(MsgID::MSG_C2S_REQ_CHAR_LIST, xMsg);
	return 0;
}
int SGLoginProcess::OnRspEnterGame(uint32 nClientIndex, uint8* pData, uint32 nLength)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Blue,
		FString(TEXT("OnRspEnterGame !"))
	);
	SGMsg::S2CRspEnterGameServer xReceivedMsg;
	if (!xReceivedMsg.ParseFromArray(pData, nLength))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("parse S2CRspAccountLogin error %d !"), nClientIndex)
		);
		return 1;
	}
	m_xRoleID = xReceivedMsg.role_id();
	//m_pLoginWidget->SetLoadingMenu();
	m_pLoginWidget->BeforeDestroy();
	m_pLoginWidget = nullptr;
	SGCoreApp::GetInstance()->DoLoginFinish(/*false*/);
	//m_pLoginWidget->SetLoadingProgress(fFakeLoginProgress);
	return 0;
}
//void SGLoginProcess::FakeFinishLoading()
//{
//	fFakeLoginProgress += 0.2;
//	if (fFakeLoginProgress > 0.9)
//	{
//		if (m_pLoginWidget != nullptr)
//		{
//			m_pLoginWidget->BeforeDestroy();
//			m_pLoginWidget = nullptr;
//		}
//	}
//	else
//	{
//		m_pLoginWidget->SetLoadingProgress(fFakeLoginProgress);
//		SGCoreApp::GetInstance()->DoLoginFinish(true);
//	}
//}
void SGLoginProcess::OnConfigEncryptoInfoRecive()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Blue,
		FString(TEXT("On config EncryptoTypeRecive!"))
	);
	auto pNetWork = SGCoreApp::GetInstance()->GetTcpClient(m_nTcpClientIndex);
	pNetWork->SetCrypto(false);
	//
	SGMsg::C2SReqAccountLogin xMsg;
	xMsg.set_account(m_strPlayerAccount);
	xMsg.set_password("");
	xMsg.set_security_code("");
	xMsg.set_signbuff("");
	xMsg.set_loginmode(0);
	xMsg.set_device_info("deviceinfo_UE5Client");
	xMsg.set_extra_info("UE5Client");
	xMsg.set_big_area_id(2);
	xMsg.set_platform_world_type(4);
	xMsg.set_ignore_client_version_check(true);
	xMsg.set_client_version("5.3.3.0");

	SGCoreApp::GetInstance()->SendMsg(MsgID::MSG_C2S_REQ_ACCOUNT_LOGIN, xMsg);
	m_eStep = LS_LoginConfig;
}
void SGLoginProcess::OnGateEncryptoInfoRecive()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Blue,
		FString(TEXT("On gate EncryptoTypeRecive!"))
	);

	auto pNetWork = SGCoreApp::GetInstance()->GetTcpClient(m_nTcpClientIndex);
	if (m_xGateEncryptoID.head() != 0 && m_xGateEncryptoID.data() != 0)
	{
		pNetWork->SetCrypto(true);
	}
	else
	{
		pNetWork->SetCrypto(false);
	}
	SGMsg::C2SReqIdentificationInGate xMsg;
	*xMsg.mutable_config_client_id() = m_xConfigClientID;
	xMsg.set_token(m_strToken);

	pNetWork->Send(MsgID::MSG_C2S_REQ_IDENTIFICATION_IN_GATE, xMsg);
}
void SGLoginProcess::ResetToServerListState()
{
	m_eStep = LS_LoginWindow;

	auto pNetWork = SGCoreApp::GetInstance()->GetTcpClient(m_nTcpClientIndex);
	if (pNetWork == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString(TEXT("net client null !"))
		);
		return;
	}

	pNetWork->ConnectTo(m_strConfigServerIP, m_nConfigServerPort);
}