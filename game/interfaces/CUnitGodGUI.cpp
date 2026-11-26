//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/04
//
// File Name : CUnitGodGUI.cpp
//
// 신수 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CUnitGodGUI.h"
#include "../eventhandle/CEventHandleManager.h"

enum
{
    COMMAND_ATTACK_BUTTON = 7100,
    COMMAND_MAGIC1_BUTTON,
    COMMAND_MAGIC2_BUTTON,
    COMMAND_MAGIC3_BUTTON,

    COMMAND_BUILDING_GODBACK,
    COMMAND_BUILDING_BACK,
    COMMAND_BUILDING_CANCEL
};


/*======================================================*/
// 컨트롤
/*======================================================*/
bool CUnitGodGUI::interfaceControl( CEventHandler* p_receiver)
{
    refreshView();
    if (!p_receiver || !getViewState().bound)
        return false;

    if (p_receiver->isClickedButtonID(COMMAND_ATTACK_BUTTON))
    {
        m_view_model.requestAttack();
    }

    return true;
}
