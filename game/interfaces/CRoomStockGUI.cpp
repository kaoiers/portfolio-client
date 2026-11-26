//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/28
//
// File Name : CRoomStockGUI.cpp
//
// 창고 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CRoomStockGUI.h"
#include "../eventhandle/CEventHandleManager.h"

enum

{
    COMMAND_WAREHOUSE_DESTROY_BUTTON = 9600,
    COMMAND_WAREHOUSE_EX_BUTTON,

    COMMAND_BUILDING_WAREHOUSEBACK,
    COMMAND_BUILDING_BACK,
    COMMAND_BUILDING_CANCEL,
    COMMAND_BUIDING_DAMAGE_TEXT
};

/*======================================================*/
// 초기화
/*======================================================*/
void CRoomStockGUI::guiInitialize()
{
}


/*======================================================*/
// 컨트롤
/*======================================================*/
bool CRoomStockGUI::interfaceControl( CEventHandler* p_receiver)
{
    refreshView();
    if (!p_receiver || !getViewState().bound)
        return false;

    if (p_receiver->isClickedButtonID(COMMAND_WAREHOUSE_DESTROY_BUTTON))
    {
        m_view_model.requestDestroy();
    }

    return true;
}
