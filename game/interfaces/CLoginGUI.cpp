//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/22
//
// File Name : CLoginGUI.cpp
// 
// 로그인 인터페이스
// 
//////////////////////////////////////////////////////////////////////////


#include <stdafx.h>
#include "CLoginGUI.h"
#include "../CAppContext.h"
#include "../God_Game.h"
#include "../eventhandle/CEventHandleManager.h"


CLoginGUI::CLoginGUI( position2d<s16> rect /*= position2di(0,0)*/ ) : CGameGUI(rect)
{

}

/*======================================================*/
// 초기화
/*======================================================*/
void CLoginGUI::GUI_Initialize()
{
	//에디트박스 모두 공란 설정
}


/*======================================================*/
// 로긴 위도우 보이기
/*======================================================*/
void CLoginGUI::ShowLoginWindow( const bool bshow )
{
	
}


/*======================================================*/
// 회원가입윈도우 보이기
/*======================================================*/
void CLoginGUI::ShowJoinWindow( const bool bshow )
{
	
}



/*======================================================*/
// 로긴 윈도우 보이기
/*======================================================*/
void CLoginGUI::ShowLoginWindowGUI( const bool bshow )
{
	if(bshow)
	{
		Show();
		ShowLoginWindow(true);			
		ShowJoinWindow(false);

	}
	else if(!bshow)
	{
		ShowLoginWindow(false);
		ShowJoinWindow(true);
		Hide();
	}
}


/*======================================================*/
// 컨트롤
/*======================================================*/
bool CLoginGUI::interface_control( CEventHandler* pReceiver )
{
	if(pReceiver->isClickedButtonID(GUI_LOGIN_BUTTON_SIGNUP))
	{
		ShowLoginWindow(false);
		ShowJoinWindow(true);				
	}
	else if(pReceiver->isClickedButtonID(GUI_JOIN_BUTTON_BACK))
	{
		ShowLoginWindow(true);
		ShowJoinWindow(false);			
	}
	else if(pReceiver->isClickedButtonID(GUI_LOGIN_BUTTON_OK))
	{
		//std::tr1::shared_ptr<PACKET_ACCOUNT_LOGIN_CL_LN_REQ> account(CreateLoginPacket());

		//NETWORK
		//PACKET_ACCOUNT_LOGIN_CL_LN_REQ* account = new PACKET_ACCOUNT_LOGIN_CL_LN_REQ();



		//strcpy_s(account->m_nickname, GetMuiltiByteStringOfEditBox(FindElementByID(GUI_LOGIN_EDIT_ID)).c_str());
		//strcpy_s(account->m_password, GetMuiltiByteStringOfEditBox(FindElementByID(GUI_LOGIN_EDIT_PASSWORD)).c_str());
		
		this->Hide();
		
		CAppContext::GetGodGame()->GameLoading();



	}
	else if(pReceiver->isClickedButtonID(GUI_JOIN_BUTTON_CONFIRM))
	{
		//NETWORK
// 		stringc password1 = GetMuiltiByteStringOfEditBox(FindElementByID(GUI_JOIN_EDIT_NEWPASSWORD)),
// 			password2 = GetMuiltiByteStringOfEditBox(FindElementByID(GUI_JOIN_EDIT_NEWPASSWORD_CONFIRM));
// 
// 		if(password1 == password2)
// 		{
// 			std::tr1::shared_ptr<PACKET_ACCOUNT_MAKEACCOUNT_CL_LN_REQ> account(CreateMakeAccountPacket());
// 			strcpy_s(account->m_nickname, GetMuiltiByteStringOfEditBox(FindElementByID(GUI_JOIN_EDIT_NEWID)).c_str());
// 			strcpy_s(account->m_password, GetMuiltiByteStringOfEditBox(FindElementByID(GUI_JOIN_EDIT_NEWPASSWORD)).c_str());
// 			CNetworkManager* pNetwork = CAppContext::GetGodGame()->getNetworkManager();				
// 			pNetwork->SendPacket(account.get() , sizeof(PACKET_ACCOUNT_MAKEACCOUNT_CL_LN_REQ));
// 		}
	}

	return true;
}