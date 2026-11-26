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
#include "../objects/CGameUnitWorker.h"
#include "../eventhandle/CEventHandleManager.h"
#include "../objects/CGameObjectManager.h"
#include "../objects/CGameRoom.h"

/*======================================================*/
// 주인 오브젝트 설정
/*======================================================*/
void CUnitWorkerGUI::setOwner( CGameObject *obj)
{
    m_owner = dynamic_cast<CGameUnitWorker *>(obj);
}

/*======================================================*/
// 컨트롤
/*======================================================*/
bool CUnitWorkerGUI::interfaceControl( CEventHandler* p_receiver)
{
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
        m_owner->setCommandType(com_collection);

    }
    else if (p_receiver->isClickedButtonID(COMMAND_ATTACK_BUTTON))
    {
        m_owner->setCommandType(com_none);
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
        m_owner->cancelControl();
        m_owner->addBuilding(BUILDING_JAIL);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_WAREHOUSE))
    {
        m_owner->cancelControl();
        m_owner->addBuilding(BUILDING_WAREHOUSE);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_WAITING))
    {
        m_owner->cancelControl();
        m_owner->addBuilding(BUILDING_WAITINGROOM);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_TOWER))
    {
        m_owner->cancelControl();
        m_owner->addBuilding(BUILDING_TOWER);
    }

    if (p_receiver->isClickedButtonID(COMMAND_BUILDING_CANCEL))
    {
        m_owner->cancelBuilding();
    }

    if (p_receiver->isClickedButtonID(COMMAND_BUILDING_FARM))
    {
        m_owner->cancelControl();
        m_owner->addBuilding(BUILDING_FARM);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_WOOD))
    {
        m_owner->cancelControl();
        m_owner->addBuilding(BUILDING_WOOD);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_GOLD))
    {
        m_owner->cancelControl();
        m_owner->addBuilding(BUILDING_GOLD);
    }

    else if (p_receiver->isClickedButtonID(COMMAND_BUILDING_FRIEND))
    {
        m_owner->cancelControl();
        m_owner->addBuilding(BUILDING_FRIEND);
    }

    return true;
}
