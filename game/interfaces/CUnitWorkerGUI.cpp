//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/26
//
// File Name : CUnitWorkerGUI.cpp
//
// 일꾼 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CUnitWorkerGUI.h"
#include "../eventhandle/CEventHandleManager.h"


/*======================================================*/
// 컨트롤
/*======================================================*/
bool CUnitWorkerGUI::interfaceControl( CEventHandler* p_receiver)
{
    refreshView();
    if (!p_receiver || !getViewState().bound)
        return false;

    if (p_receiver->isClickedButtonID(COMMAND_BUILDING_BUTTON))
    {
        this->showGroup("building_main", true);
        this->showGroup("building1", true);
        this->showGroup("building2", false);
        this->showGroup("base", false);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_BACK))
    {
        this->showGroup("building_main", false);
        this->showGroup("building1", false);
        this->showGroup("building2", false);
        this->showGroup("base", true);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_WORKING_BUTTON))
    {
        m_view_model.requestCollect();

    }
    else if (p_receiver->isClickedButtonID(COMMAND_ATTACK_BUTTON))
    {
        m_view_model.requestIdle();
    }

    if (p_receiver->isClickedButtonID(COMMAND_BUILDING_ARROWL))
    {
        this->showGroup("building1", true);
        this->showGroup("building2", false);
    }
    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_ARROWR))
    {
        this->showGroup("building1", false);
        this->showGroup("building2", true);
    }

    if (p_receiver->isClickedButtonID(COMMAND_BUILDING_JAIL))
    {
        m_view_model.requestBuild(BUILDING_JAIL);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_WAREHOUSE))
    {
        m_view_model.requestBuild(BUILDING_WAREHOUSE);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_WAITING))
    {
        m_view_model.requestBuild(BUILDING_WAITINGROOM);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_TOWER))
    {
        m_view_model.requestBuild(BUILDING_TOWER);
    }

    if (p_receiver->isClickedButtonID(COMMAND_BUILDING_CANCEL))
    {
        m_view_model.requestCancelBuilding();
    }

    if (p_receiver->isClickedButtonID(COMMAND_BUILDING_FARM))
    {
        m_view_model.requestBuild(BUILDING_FARM);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_WOOD))
    {
        m_view_model.requestBuild(BUILDING_WOOD);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_GOLD))
    {
        m_view_model.requestBuild(BUILDING_GOLD);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_FRIEND))
    {
        m_view_model.requestBuild(BUILDING_FRIEND);
    }

    return true;
}
