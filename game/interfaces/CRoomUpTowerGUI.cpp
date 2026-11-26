//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/30
//
// File Name : CRoomUpTowerGUI.cpp
// 
// 업그레이드 타워 인터페이스
// 
//////////////////////////////////////////////////////////////////////////


#include <stdafx.h>
#include "CRoomUpTowerGUI.h"
#include "../eventhandle/CEventHandleManager.h"



enum {	

	COMMAND_BUILDING_BACKGROUND = 9800,
	COMMAND_TOWER_LEVELUP_BUTTON,
	COMMAND_TOWER_DESTROY_BUTTON,
	COMMAND_BUILDING_TOWERBACK,
	COMMAND_BUILDING_BACK,
	COMMAND_BUILDING_CANCEL,
	COMMAND_BUIDING_DAMAGE_TEXT

};



/*======================================================*/
// 컨트롤
/*======================================================*/
bool CRoomUpTowerGUI::interfaceControl( CEventHandler* p_receiver )
{

	if(p_receiver->isClickedButtonID(COMMAND_BUILDING_CANCEL ))
	{
		
	}


	return true;
}


/*======================================================*/
// 초기화
/*======================================================*/
void CRoomUpTowerGUI::guiInitialize()
{
	//m_pDamageText = dynamic_cast<CTextGUI*>(FindElementByID(COMMAND_BUIDING_DAMAGE_TEXT));
}




/*======================================================*/
// 주인 오브젝트 설정
/*======================================================*/
void CRoomUpTowerGUI::setOwner( CGameObject *obj )
{
	
	//setDamage( m_pOwner->getRoomHp() , m_pOwner->getTotalRoomHP());
}
