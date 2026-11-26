//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/08
//
// File Name : CunitArmyGUI.cpp
//
// 전사 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CUnitArmyGUI.h"
#include "../eventhandle/CEventHandleManager.h"

enum
{
    COMMAND_ARMY_BUILDING_DEFENCE_BUTTON =7300,
    COMMAND_ARMY_PATROL_BUTTON,
    COMMAND_ARMY_LV_BUTTON,

    COMMAND_BUILDING_ARMYBACK,
    COMMAND_BUILDING_BACK,
    COMMAND_BUILDING_CANCEL
};

/*======================================================*/
// 컨트롤
/*======================================================*/
bool CUnitArmyGUI::interfaceControl( CEventHandler* p_receiver)
{
    refreshView();
    if (!p_receiver || !getViewState().bound)
        return false;

    if (p_receiver->isClickedButtonID(COMMAND_ARMY_BUILDING_DEFENCE_BUTTON))
    {
        m_view_model.requestGuard();
    }

    return true;
}
/*======================================================*/
// 초기화
/*======================================================*/
void CUnitArmyGUI::guiInitialize()
{
}

