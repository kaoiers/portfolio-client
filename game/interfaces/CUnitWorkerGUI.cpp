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
void CUnitWorkerGUI::SetOwner( CGameObject *obj )
{
	m_pOwner = dynamic_cast<CGameUnitWorker *>(obj);
}


/*======================================================*/
// 컨트롤
/*======================================================*/
bool CUnitWorkerGUI::interface_control( CEventHandler* pReceiver )
{


	if(pReceiver->isClickedButtonID(COMMAND_BUILDING_BUTTON))
	{
		this->showGroup("building_main", true);
		this->showGroup("building1", true);		
		this->showGroup("building2", false);
		this->showGroup("base", false);	

		
	}
	
	else if(pReceiver->isClickedButtonID(COMMAND_BUILDING_BACK))
	{
		this->showGroup("building_main", false);
		this->showGroup("building1", false);		
		this->showGroup("building2", false);
		this->showGroup("base", true);	
	}

	else if(pReceiver->isClickedButtonID(COMMAND_WORKING_BUTTON))
	{
		//this->getGUIManager();
		
		m_pOwner->setCommandType(com_collection);
		
		
	}else if(pReceiver->isClickedButtonID(COMMAND_ATTACK_BUTTON))
	{
		m_pOwner->setCommandType(com_none);

	}



	if(pReceiver->isClickedButtonID(COMMAND_BUILDING_ARROWL))
	{
		this->showGroup("building1", true);		
		this->showGroup("building2", false);		
	}
	else if(pReceiver->isClickedButtonID(COMMAND_BUILDING_ARROWR))
	{
		this->showGroup("building1", false);		
		this->showGroup("building2", true);

	}

	
	
	if(pReceiver->isClickedButtonID(COMMAND_BUILDING_JAIL))
	{
		m_pOwner->CancelControl();
		m_pOwner->AddBuilding(BUILDING_JAIL);
	}	

	else if(pReceiver->isClickedButtonID(COMMAND_BUILDING_WAREHOUSE))
	{		
		m_pOwner->CancelControl();
		m_pOwner->AddBuilding(BUILDING_WAREHOUSE);
	}



	else if(pReceiver->isClickedButtonID(COMMAND_BUILDING_WAITING))
	{
		m_pOwner->CancelControl();
		m_pOwner->AddBuilding(BUILDING_WAITINGROOM);
	}


	else if(pReceiver->isClickedButtonID(COMMAND_BUILDING_TOWER))
	{
		m_pOwner->CancelControl();
		m_pOwner->AddBuilding(BUILDING_TOWER);

	}


	if(pReceiver->isClickedButtonID(COMMAND_BUILDING_CANCEL))
	{
		m_pOwner->CancelBuilding();
	}





	if(pReceiver->isClickedButtonID(COMMAND_BUILDING_FARM))
	{
		m_pOwner->CancelControl();
		m_pOwner->AddBuilding(BUILDING_FARM);
	}
	
	else if(pReceiver->isClickedButtonID(COMMAND_BUILDING_WOOD))
	{
		m_pOwner->CancelControl();
		m_pOwner->AddBuilding(BUILDING_WOOD);
	}
	
	else if(pReceiver->isClickedButtonID(COMMAND_BUILDING_GOLD))
	{
		m_pOwner->CancelControl();
		m_pOwner->AddBuilding(BUILDING_GOLD);
	}
	
	else if(pReceiver->isClickedButtonID(COMMAND_BUILDING_FRIEND))
	{
		m_pOwner->CancelControl();
		m_pOwner->AddBuilding(BUILDING_FRIEND);
	}		






	return true;
}