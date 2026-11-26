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
#include "../CAppcontext.h"
#include "../God_Game.h"
#include "../eventhandle/CEventHandleManager.h"

CLoginGUI::CLoginGUI( position2d<s16> rect /*= position2di(0,0)*/) : CGameGUI(rect)
{
}

/*======================================================*/
// 초기화
/*======================================================*/
void CLoginGUI::guiInitialize()
{
    //에디트박스 모두 공란 설정
}

/*======================================================*/
// 로긴 위도우 보이기
/*======================================================*/
void CLoginGUI::showLoginWindow( const bool bshow)
{
}

/*======================================================*/
// 회원가입윈도우 보이기
/*======================================================*/
void CLoginGUI::showJoinWindow( const bool bshow)
{
}

/*======================================================*/
// 로긴 윈도우 보이기
/*======================================================*/
void CLoginGUI::showLoginWindowGui( const bool bshow)
{
    if (bshow)
    {
        show();
        showLoginWindow(true);
        showJoinWindow(false);
    }
    else if (!bshow)
    {
        showLoginWindow(false);
        showJoinWindow(true);
        hide();
    }
}

/*======================================================*/
// 컨트롤
/*======================================================*/
bool CLoginGUI::interfaceControl( CEventHandler* p_receiver)
{
    if (p_receiver->isClickedButtonID(GUI_LOGIN_BUTTON_SIGNUP))
    {
        showLoginWindow(false);
        showJoinWindow(true);
    }
    else if (p_receiver->isClickedButtonID(GUI_JOIN_BUTTON_BACK))
    {
        showLoginWindow(true);
        showJoinWindow(false);
    }
    else if (p_receiver->isClickedButtonID(GUI_LOGIN_BUTTON_OK))
    {
        this->hide();

        CAppContext::getGodGame()->gameLoading();
    }
    else if (p_receiver->isClickedButtonID(GUI_JOIN_BUTTON_CONFIRM))
    {
    }

    return true;
}
