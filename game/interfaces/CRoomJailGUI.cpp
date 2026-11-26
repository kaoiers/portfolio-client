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
void CRoomJailGUI::SetOwner( CGameObject *obj )
{
	m_pOwner = dynamic_cast<CGameRoomJail *>(obj);

		//setDamage( m_pOwner->getRoomHp() , m_pOwner->getTotalRoomHP());
}



/*======================================================*/
// 컨트롤
/*======================================================*/
bool CRoomJailGUI::interface_control( CEventHandler* pReceiver )
{
	if(pReceiver->isClickedButtonID(COMMAND_PRISON_FREE_BUTTON))
	{
		//printf("헤헤\n");
	}
	
	else if(pReceiver->isClickedButtonID(COMMAND_DESTROY_BUTTON))
	{
		m_pOwner->Explosion();	

		m_pOwner->DeleteRoom();
	}

	
	return true;
}



/*======================================================*/
// 초기화
/*======================================================*/
void CRoomJailGUI::GUI_Initialize()
{
	//m_pDamageText = dynamic_cast<CTextGUI*>(FindElementByID(COMMAND_BUIDING_DAMAGE_TEXT));
}


