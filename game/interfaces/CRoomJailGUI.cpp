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
#include "../objects/CGameRoomJail.h"
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
// 주인 오브젝트 설정
/*======================================================*/
void CRoomJailGUI::setOwner( CGameObject *obj )
{
	m_owner = dynamic_cast<CGameRoomJail *>(obj);

}



/*======================================================*/
// 컨트롤
/*======================================================*/
bool CRoomJailGUI::interfaceControl( CEventHandler* p_receiver )
{
	if(p_receiver->isClickedButtonID(COMMAND_PRISON_FREE_BUTTON))
	{
	}
	
	else if(p_receiver->isClickedButtonID(COMMAND_DESTROY_BUTTON))
	{
		m_owner->explosion();	

		m_owner->deleteRoom();
	}

	
	return true;
}



/*======================================================*/
// 초기화
/*======================================================*/
void CRoomJailGUI::guiInitialize()
{
}


