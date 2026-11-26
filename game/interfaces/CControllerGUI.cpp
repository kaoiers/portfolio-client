//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/02/11
//
// File Name : CControllerGUI.cpp
// 
// 컨트롤 GUI 인터페이스 관리
// 
//////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "../interfaces/IGameGUI.h"
#include "../interfaces/CGUIManager.h"
#include "../interfaces/CControllerGUI.h"


#include "../interfaces/CUnitGodGUI.h"
#include "../interfaces/CUnitWorkerGUI.h"
#include "../interfaces/CUnitArmyGUI.h"
#include "../interfaces/CRoomJailGUI.h"
#include "../interfaces/CRoomCommunityGUI.h"
#include "../interfaces/CRoomStockGUI.h"
#include "../interfaces/CRoomUpTowerGUI.h"

#include "../objects/CGameUnitGod.h"
#include "../objects/CGameUnitWorker.h"
#include "../objects/CGameUnitArmy.h"


#include "../objects/CGameRoomJail.h"
#include "../objects/CGameRoomCommunity.h"
#include "../objects/CGameRoomStock.h"









CControllerGUI* CControllerGUI::p_instance = NULL;

CControllerGUI::CControllerGUI() : 
m_current_gui(0)
{
	p_instance = this;	
}



CControllerGUI::~CControllerGUI() {}


/*======================================================*/
// 신수GUI 컨트롤 지정
/*======================================================*/
void CControllerGUI::setGodGUI( CGameUnitGod* p_god )
{
	m_unit_god_gui->setOwner(p_god); 
	setGuiController(m_unit_god_gui);
}


/*======================================================*/
// 일꾼 GUI 컨트롤 지정
/*======================================================*/
void CControllerGUI::setWorkerGUI( CGameUnitWorker* p_worker )
{
	m_unit_worker_gui->setOwner(p_worker); 
	setGuiController(m_unit_worker_gui);
	m_unit_worker_gui->showGroup("building_main", false);
	m_unit_worker_gui->showGroup("building1", false);		
	m_unit_worker_gui->showGroup("building2", false);
	m_unit_worker_gui->showGroup("base", true);
}


/*======================================================*/
// 병사 GUI 컨트롤 지정
/*======================================================*/
void CControllerGUI::setArmyGUI( CGameUnitArmy* p_army )
{
	m_unit_army_gui->setOwner(p_army);
	setGuiController(m_unit_army_gui);

}


/*======================================================*/
// 현재 GUI 지정
/*======================================================*/
void CControllerGUI::setGuiController( CGameGUI* p_gui )
{
	if(m_current_gui)
	{
		m_current_gui->hide();
	}

	m_current_gui = p_gui;

	m_current_gui->show();

}


/*======================================================*/
// 인스턴스
/*======================================================*/
CControllerGUI* CControllerGUI::instance()
{
	return p_instance;

}



/*======================================================*/
// 비활성화 시키기
/*======================================================*/
void CControllerGUI::disableGui()
{
	if(m_current_gui)
	{
		m_current_gui->hide();
	}

	m_current_gui = 0;

}




/*======================================================*/
// 현재 컨트롤 GUI
/*======================================================*/
CGameGUI* CControllerGUI::setCurrentControlGUI( CGameObject * obj )
{

	

	return NULL;

}
