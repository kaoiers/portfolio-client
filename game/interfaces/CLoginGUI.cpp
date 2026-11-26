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




		
		this->Hide();
		
		CAppContext::GetGodGame()->GameLoading();



	}
	else if(pReceiver->isClickedButtonID(GUI_JOIN_BUTTON_CONFIRM))
	{
	}

	return true;
}