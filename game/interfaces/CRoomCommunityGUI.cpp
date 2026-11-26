//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/08/01
//
// File Name : CRoomCommunityGUI.cpp
// 
// 대기실 인터페이스
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CRoomCommunityGUI.h"
#include "../objects/CGameRoomCommunity.h"
#include "../eventhandle/CEventHandleManager.h"
#include "CGUIManager.h"


enum{

	COMMAND_COMMUNITY_REQUEST_FORCE = 9500,
	COMMAND_COMMUNITY_VISIT_FRIEND ,
	COMMAND_COMMUNITY_DESTROY_BUTTON,

	COMMAND_BUILDING_FRIENDBACK,
	COMMAND_BUILDING_BACK,
	COMMAND_BUILDING_CANCEL,
//COMMAND_COMMUNITY_FRIENDLIST_LEFT_BUTTON,
//COMMAND_COMMUNITY_FRIENDLIST_RIGHT_BUTTON,
	COMMAND_BUIDING_DAMAGE_TEXT

};




/*======================================================*/
// 친구 리스트 리셋
/*======================================================*/
void CRoomCommunityGUI::ResetFriendsList()
{



	for(unsigned int i=0; i < friend_button_counts; i++)
	{
		unsigned int idx = ((m_uCurrent_page - 1) * friend_button_counts) + i;
	

	}
}


/*======================================================*/
// 인터페이스 컨트롤
/*======================================================*/
bool CRoomCommunityGUI::interface_control( CEventHandler* pReceiver )
{

	//m_pFriendName[0]->getPosition();


	if(pReceiver->isClickedButtonID(COMMAND_BUILDING_CANCEL))
	{
		m_pOwner->Explosion();	

		m_pOwner->DeleteRoom();
	}



	return true;
}



/*======================================================*/
// 초기화
/*======================================================*/
void CRoomCommunityGUI::GUI_Initialize()
{
	//m_pDamageText = dynamic_cast<CTextGUI*>(FindElementByID(COMMAND_BUIDING_DAMAGE_TEXT));

	CGUIManager*	pGUIMan =  CGUIManager::GetInstance();


	int startPosX = -390;
	int startPosY = 580;

	unsigned int ImagesizeX = 90;

	unsigned int button_id = COMMAND_BUIDING_DAMAGE_TEXT+1;



	for(unsigned int i=0; i < friend_button_counts; i++)
	{
		position2d<s32> pos(0,0);

		pos.Y += 50; 


	}



	


	

}


/*======================================================*/
// 주인 오프벡트 설정
/*======================================================*/
void CRoomCommunityGUI::SetOwner( CGameObject *obj )
{
	m_pOwner = dynamic_cast<CGameRoomCommunity* >(obj);

	setDamage( m_pOwner->getRoomHp() , m_pOwner->getTotalRoomHP());

	ResetFriendsList();
}





/*======================================================*/
// 프렌드 리스트 추가
/*======================================================*/
void CRoomCommunityGUI::addFriendList( const char* friend_name, unsigned int friend_id, const char* friend_picture_file /*= 0 */ )
{
	friend_button_id++;

	m_friend_id = friend_id;

	FriendInfo	temp_friend;
	temp_friend.friend_id = friend_id;
	temp_friend.friend_name = friend_name;
	temp_friend.friend_picture_file = friend_picture_file;
	//temp_friend.friend_button_id = friend_button_id;


}



/*======================================================*/
// 사진 설정
/*======================================================*/
void CRoomCommunityGUI::setFriendPicture( unsigned int friend_id, size_t stream_size, char* pStream )
{

}


CRoomCommunityGUI::CRoomCommunityGUI( position2d<s32> rect /*= position2di(0,0)*/ ) :
CGameGUI(rect),  friend_button_id(COMMAND_BUIDING_DAMAGE_TEXT+1), m_uCurrent_page(1) {}

