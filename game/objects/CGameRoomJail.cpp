//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/09/30
//
// File Name : CGameRoomJail.cpp
//
// 감옥 클래스
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameRoomJail.h"

CGameRoomJail::CGameRoomJail(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res,
    const vector3df& pos,
    const vector3df& rot,
    const vector3df& scale)
    : CGameRoom(owner, objtype, btype, res, pos, rot, scale)
{
}

CGameRoomJail::CGameRoomJail(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res)
    : CGameRoom(owner, objtype, btype, res)
{
}

/*======================================================*/
// 컨트롤 초기화
/*======================================================*/
void CGameRoomJail::enterControl()
{
}

/*======================================================*/
// 컨트롤 어데이트
/*======================================================*/
void CGameRoomJail::updateControl( CEventHandler* p_receiver)
{
}

/*======================================================*/
// 컨트롤 종료
/*======================================================*/
void CGameRoomJail::exitControl()
{
}

/*======================================================*/
// 업데이트
/*======================================================*/
void CGameRoomJail::update( const u32 time_ms)
{
    buildingUpdate();
}
