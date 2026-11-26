//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/04/04
//
// File Name : CGameRoomGod.h
//
// 신수방 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef CGAME_ROOM_GOD_H
#define CGAME_ROOM_GOD_H
#include "CGameRoom.h"

/// 신수방 건물에 해당하는 모델이다.
class CGameRoomGod : public CGameRoom
{
    void initialize(const vector2di& tile_pos);

public:
    CGameRoomGod(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res, const vector2di& tile_pos,
        const vector3df& pos,
        const vector3df& rot = vector3df(0.0f, 0.0f, 0.0f),
        const vector3df& scale = vector3df(1.0f, 1.0f, 1.0f));

    void enterControl();
    void updateControl(CEventHandler* p_receiver);
    void exitControl();
    void update(const u32 time_ms);
    void extraNodeSetting() {};

    CGameRoomGod(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res, const vector2di& tile_pos);

    virtual bool handleMessage(const Telegram& msg) { return true; }

    virtual ~CGameRoomGod() {};
};

#endif
