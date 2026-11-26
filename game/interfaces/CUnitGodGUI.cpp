//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/08/04
//
// File Name : CUnitGodGUI.cpp
// 
// 신수 인터페이스
// 
//////////////////////////////////////////////////////////////////////////



#include <stdafx.h>
#include "CUnitGodGUI.h"
#include "../objects/CGameUnitGod.h"
#include "../eventhandle/CEventHandleManager.h"

enum 
{
	COMMAND_ATTACK_BUTTON = 7100,
	COMMAND_MAGIC1_BUTTON,
	COMMAND_MAGIC2_BUTTON,
	COMMAND_MAGIC3_BUTTON,

	COMMAND_BUILDING_GODBACK,
	COMMAND_BUILDING_BACK,
	COMMAND_BUILDING_CANCEL
};


/*======================================================*/
// 주인 오브젝트 설정
/*======================================================*/
void CUnitGodGUI::setOwner( CGameObject *obj )
{
	m_owner = dynamic_cast<CGameUnitGod *>(obj);
}




/*======================================================*/
// 컨트롤
/*======================================================*/
bool CUnitGodGUI::interfaceControl( CEventHandler* p_receiver )
{


	if(p_receiver->isClickedButtonID(COMMAND_ATTACK_BUTTON))
	{
		m_owner->setCommandType(com_attack);		
	
	
	}



	return true;
}