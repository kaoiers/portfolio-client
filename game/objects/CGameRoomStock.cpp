//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/09/28
//
// File Name : CGameRoomStock.h
//
// 창고 클래스
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameRoomStock.h"

CGameRoomStock::CGameRoomStock(OwnerType owner, u32 objtype, u32 btype,
    const ROOM_RESOURCE* res,
    const vector3df& pos,
    const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/,
    const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/)
    : CGameRoom(owner, objtype, btype, res, pos, rot, scale)
{
}

CGameRoomStock::CGameRoomStock(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res)
    : CGameRoom(owner, objtype, btype, res)
{
}

/*======================================================*/
// 컨트롤 초기화
/*======================================================*/
void CGameRoomStock::enterControl()
{
}

/*======================================================*/
// 컨트롤 업데이트
/*======================================================*/
void CGameRoomStock::updateControl( CEventHandler* p_receiver)
{
}

/*======================================================*/
// 컨트롤 종료
/*======================================================*/
void CGameRoomStock::exitControl()
{
}

/*======================================================*/
// 업데이트
/*======================================================*/
void CGameRoomStock::update( const u32 time_ms)
{
    buildingUpdate();
}
