//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/16
//
// File Name : CGameRoomCommunity.cpp
//
// 통신방 클래스
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameRoomCommunity.h"
#include "../interfaces/CControllerGUI.h"
#include <map>
#include "../shader/CLightEffectManager.h"

CGameRoomCommunity::CGameRoomCommunity(OwnerType owner, u32 objtype, u32 btype,
    const ROOM_RESOURCE* res,
    const vector3df& pos,
    const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/,
    const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/)
    : CGameRoom(owner, objtype, btype, res, pos, rot, scale)
{
}

CGameRoomCommunity::CGameRoomCommunity(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res)
    : CGameRoom(owner, objtype, btype, res)
{
}

/*======================================================*/
// 컨트롤 초기화
/*======================================================*/
void CGameRoomCommunity::enterControl()
{
    CControllerGUI::instance()->setCurrentControlGUI(this);
}

/*======================================================*/
// 컨트롤 업데이트
/*======================================================*/
void CGameRoomCommunity::updateControl( CEventHandler* p_receiver)
{
}

/*======================================================*/
// 컨트롤 종료시 처리
/*======================================================*/
void CGameRoomCommunity::exitControl()
{
}

/*======================================================*/
// 업데이트
/*======================================================*/
void CGameRoomCommunity::update( const u32 time_ms)
{
    buildingUpdate();
}

CGameRoomCommunity::~CGameRoomCommunity()
{
}
