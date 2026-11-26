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









CControllerGUI* CControllerGUI::pInstance = NULL;

CControllerGUI::CControllerGUI() : 
m_pCurrentGUI(0)
{
	pInstance = this;	
}



CControllerGUI::~CControllerGUI() {}

/*======================================================*/
// 초기화
/*======================================================*/
void CControllerGUI::init( cLua *pLua )
{
	InitUnitGUI( pLua );

	InitRoomGUI( pLua );

}


/*======================================================*/
// 신수GUI 컨트롤 지정
/*======================================================*/
void CControllerGUI::setGodGUI( CGameUnitGod* pGod )
{
	m_pUnitGodGUI->SetOwner(pGod); 
	SetGUIController(m_pUnitGodGUI);
}


/*======================================================*/
// 일꾼 GUI 컨트롤 지정
/*======================================================*/
void CControllerGUI::setWorkerGUI( CGameUnitWorker* pWorker )
{
	m_pUnitWorkerGUI->SetOwner(pWorker); 
	SetGUIController(m_pUnitWorkerGUI);
	m_pUnitWorkerGUI->showGroup("building_main", false);
	m_pUnitWorkerGUI->showGroup("building1", false);		
	m_pUnitWorkerGUI->showGroup("building2", false);
	m_pUnitWorkerGUI->showGroup("base", true);
}


/*======================================================*/
// 병사 GUI 컨트롤 지정
/*======================================================*/
void CControllerGUI::setArmyGUI( CGameUnitArmy* pArmy )
{
	m_pUnitArmyGUI->SetOwner(pArmy);
	SetGUIController(m_pUnitArmyGUI);

}


/*======================================================*/
// 현재 GUI 지정
/*======================================================*/
void CControllerGUI::SetGUIController( CGameGUI* pGUI )
{
	if(m_pCurrentGUI)
	{
		m_pCurrentGUI->Hide();
	}

	m_pCurrentGUI = pGUI;

	m_pCurrentGUI->Show();

}


/*======================================================*/
// 인스턴스
/*======================================================*/
CControllerGUI* CControllerGUI::Instance()
{
	return pInstance;

}



/*======================================================*/
// 비활성화 시키기
/*======================================================*/
void CControllerGUI::DisableGUI()
{
	if(m_pCurrentGUI)
	{
		m_pCurrentGUI->Hide();
	}

	m_pCurrentGUI = 0;

}


/*======================================================*/
// 유닛GUI초기화
/*======================================================*/
void CControllerGUI::InitUnitGUI( cLua *pLua )
{



}

/*======================================================*/
//룸 GUI 초기화
/*======================================================*/
void CControllerGUI::InitRoomGUI( cLua *pLua )
{

}



/*======================================================*/
// 현재 컨트롤 GUI
/*======================================================*/
CGameGUI* CControllerGUI::setCurrentControlGUI( CGameObject * obj )
{

	

	return NULL;

}
