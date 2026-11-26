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
#include "../eventhandle/CEventHandleManager.h"
#include "CGUIManager.h"

enum{

    COMMAND_COMMUNITY_REQUEST_FORCE = 9500,
    COMMAND_COMMUNITY_VISIT_FRIEND,
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
void CRoomCommunityGUI::resetFriendsList()
{
    for (u32 i=0; i < friend_button_counts; i++)
    {
        u32 idx = ((m_current_page - 1) * friend_button_counts) + i;
    }
}

/*======================================================*/
// 인터페이스 컨트롤
/*======================================================*/
bool CRoomCommunityGUI::interfaceControl( CEventHandler* p_receiver)
{
    refreshView();
    if (!p_receiver || !getViewState().bound)
        return false;

    //m_pFriendName[0]->getPosition();

    if (p_receiver->isClickedButtonID(COMMAND_BUILDING_CANCEL))
    {
        m_view_model.requestDestroy();
    }

    return true;
}

/*======================================================*/
// 초기화
/*======================================================*/
void CRoomCommunityGUI::guiInitialize()
{
    CGUIManager* p_gui_man = CGUIManager::getInstance();

    s32 start_pos_x = -390;
    s32 start_pos_y = 580;

    u32 image_size_x = 90;

    u32 button_id = COMMAND_BUIDING_DAMAGE_TEXT+1;

    for (u32 i=0; i < friend_button_counts; i++)
    {
        position2d<s16> pos(0, 0);

        pos.Y += 50;
    }
}

/*======================================================*/
// 주인 오프벡트 설정
/*======================================================*/
void CRoomCommunityGUI::setOwner( CGameObject *obj)
{
    CRoomGUI::setOwner(obj);

    resetFriendsList();
}

/*======================================================*/
// 프렌드 리스트 추가
/*======================================================*/
void CRoomCommunityGUI::addFriendList( const char* friend_name, u32 friend_id, const char* friend_picture_file /*= 0 */)
{
    friend_button_id++;

    m_friend_id = friend_id;

    FriendInfo temp_friend;
    temp_friend.friend_id = friend_id;
    temp_friend.friend_name = friend_name;
    temp_friend.friend_picture_file = friend_picture_file;
}

/*======================================================*/
// 사진 설정
/*======================================================*/
void CRoomCommunityGUI::setFriendPicture( u32 friend_id, size_t stream_size, char* p_stream)
{
}

CRoomCommunityGUI::CRoomCommunityGUI( position2d<s16> rect /*= position2di(0,0)*/) :
    CRoomGUI(BUILDING_FRIEND, rect), friend_button_id(COMMAND_BUIDING_DAMAGE_TEXT+1), m_current_page(1) {}
