//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/01
//
// File Name : CRoomCommunityGUI.h
//
// 대기실 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#ifndef CROOM_COMMUNITY_GUI_H
#define CROOM_COMMUNITY_GUI_H

#include "IGameGUI.h"

class CGameRoomCommunity;

class CRoomCommunityGUI : public CGameGUI
{
    typedef struct
    {
        u32 friend_id;
        std::string friend_name;
        std::string friend_picture_file;
        s32 friend_button_id;

    }FriendInfo;

    CGameRoomCommunity* m_owner;

    enum
    {
        friend_button_counts = 5
    };

    CButtonGUI* m_friend_button[friend_button_counts];
    CTextGUI* m_friend_name[friend_button_counts];

    u32 m_friend_id;

    u32 m_current_page;

    virtual bool interfaceControl(CEventHandler* p_receiver);

    u32 friend_button_id;

    void resetFriendsList();

public:
    CRoomCommunityGUI(position2d<s16> rect = position2di(0, 0));

    virtual ~CRoomCommunityGUI() {};

    virtual void guiInitialize();

    virtual void setOwner(CGameObject *obj);

    void addFriendList(const char* friend_name, u32 friend_id, const char* friend_picture_file = "none");

    void setFriendPicture( u32 friend_id, size_t stream_size, char* p_stream);
};

#endif
