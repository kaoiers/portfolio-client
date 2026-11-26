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
#include "../objects/CGameRoomStock.h"
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
void CRoomStockGUI::GUI_Initialize()
{
//m_pDamageText = dynamic_cast<CTextGUI*>(FindElementByID(COMMAND_BUIDING_DAMAGE_TEXT));
}



/*======================================================*/
// 주인 오브젝트 설정
/*======================================================*/
void CRoomStockGUI::SetOwner( CGameObject *obj )
{
	m_pOwner = dynamic_cast<CGameRoomStock* >(obj);

	//	setDamage( m_pOwner->getRoomHp() , m_pOwner->getTotalRoomHP());
}



/*======================================================*/
// 컨트롤
/*======================================================*/
bool CRoomStockGUI::interface_control( CEventHandler* pReceiver )
{

	if(pReceiver->isClickedButtonID(COMMAND_WAREHOUSE_DESTROY_BUTTON ))
	{
		m_pOwner->Explosion();	

		m_pOwner->DeleteRoom();
	}

	return true;
}
