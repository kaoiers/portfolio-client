//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/09/30
//
// File Name : CGameRoomJail.h
//
// 감옥 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef CGAME_ROOM_JAIL_H
#define CGAME_ROOM_JAIL_H
#include "CGameRoom.h"

/// 감옥 건물의 제어 및 갱신 동작을 표현한다.
class CGameRoomJail : public CGameRoom
{
public:
    CGameRoomJail(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res,
        const vector3df& pos,
        const vector3df& rot = vector3df(0.0f, 0.0f, 0.0f),
        const vector3df& scale = vector3df(1.0f, 1.0f, 1.0f));

    void enterControl();
    void updateControl(CEventHandler* p_receiver);
    void exitControl();
    void update(const u32 time_ms);
    void extraNodeSetting() {};
    bool handleMessage(const Telegram& msg) { return true; }

    CGameRoomJail(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res);

    virtual ~CGameRoomJail() {};
};

#endif
