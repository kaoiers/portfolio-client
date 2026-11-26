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
#include "../interfaces/CControllerGUI.h"

CGameRoomStock::CGameRoomStock(OwnerType owner, unsigned int objtype, unsigned int btype,
							   const ROOM_RESOURCE* res, 
							   const vector3df& pos, 
							   const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
							   const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
							    : CGameRoom(owner, objtype, btype, res, pos, rot, scale)
{

}

CGameRoomStock::CGameRoomStock(OwnerType owner, unsigned int objtype, unsigned int btype, const ROOM_RESOURCE* res )
: CGameRoom(owner, objtype, btype, res)
{

}


/*======================================================*/
// 컨트롤 초기화
/*======================================================*/
void CGameRoomStock::enter_control()
{
	CControllerGUI::Instance()->setCurrentControlGUI(this);

}


/*======================================================*/
// 컨트롤 업데이트
/*======================================================*/
void CGameRoomStock::update_control( CEventHandler* pReceiver )
{

}


/*======================================================*/
// 컨트롤 종료
/*======================================================*/
void CGameRoomStock::exit_control()
{

}


/*======================================================*/
// 업데이트
/*======================================================*/
void CGameRoomStock::update( const u32 timeMs )
{
	BuildingUpdate();

}