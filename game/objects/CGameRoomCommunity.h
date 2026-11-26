//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/16
//
// File Name : CGameRoomCommunity.h
//
// 통신방 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef CGAME_ROOM_COMMUNITY_H
#define CGAME_ROOM_COMMUNITY_H

#include "CGameRoom.h"

/// 통신방의 건물 상태와 제어 동작을 표현한다.
class CGameRoomCommunity : public CGameRoom
{
public:
    CGameRoomCommunity(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res,
        const vector3df& pos,
        const vector3df& rot = vector3df(0.0f, 0.0f, 0.0f),
        const vector3df& scale = vector3df(1.0f, 1.0f, 1.0f));

    virtual void enterControl();

    virtual void updateControl(CEventHandler* p_receiver);

    virtual void exitControl();

    virtual void update(const u32 time_ms);

    virtual void extraNodeSetting() { setOnebyOneNode(); };

    CGameRoomCommunity(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res);

    virtual bool handleMessage(const Telegram& msg) { return true; }

    virtual ~CGameRoomCommunity();
};

#endif
