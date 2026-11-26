//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/27
//
// File Name : CRoomJailGUI.cpp
//
// 감옥실 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CRoomJailGUI.h"
#include "../eventhandle/CEventHandleManager.h"
enum
{
    COMMAND_PRISON_FREE_BUTTON = 9000,
    COMMAND_PRISON__CONILIATORY_BUTTON,
    COMMAND_DESTROY_BUTTON,

    COMMAND_BUILDING_JAILBACK,
    COMMAND_BUILDING_BACK,
    COMMAND_BUILDING_CANCEL,
    COMMAND_BUIDING_DAMAGE_TEXT
};


/*======================================================*/
// 컨트롤
/*======================================================*/
bool CRoomJailGUI::interfaceControl( CEventHandler* p_receiver)
{
    refreshView();
    if (!p_receiver || !getViewState().bound)
        return false;

    if (p_receiver->isClickedButtonID(COMMAND_PRISON_FREE_BUTTON))
    {
    }

    else if (p_receiver->isClickedButtonID(COMMAND_DESTROY_BUTTON))
    {
        m_view_model.requestDestroy();
    }

    return true;
}

/*======================================================*/
// 초기화
/*======================================================*/
void CRoomJailGUI::guiInitialize()
{
}
