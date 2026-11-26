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

CGameRoomCommunity::CGameRoomCommunity(const OwnerType& owner, unsigned int objtype, unsigned int btype, 
									   const ROOM_RESOURCE* res, 
									   const vector3df& pos, 
									   const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
									   const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
									   : CGameRoom(owner, objtype, btype, res, pos, rot, scale)
{

}

CGameRoomCommunity::CGameRoomCommunity(const OwnerType& owner, unsigned int objtype, unsigned int btype, const ROOM_RESOURCE* res )
: CGameRoom(owner, objtype, btype, res)
{
	
}

/*======================================================*/
// 컨트롤 초기화
/*======================================================*/
void CGameRoomCommunity::enter_control()
{
	CControllerGUI::Instance()->setCurrentControlGUI(this);

}


/*======================================================*/
// 컨트롤 업데이트
/*======================================================*/
void CGameRoomCommunity::update_control( CEventHandler* pReceiver )
{

}

/*======================================================*/
// 컨트롤 종료시 처리
/*======================================================*/
void CGameRoomCommunity::exit_control()
{

}


/*======================================================*/
// 업데이트
/*======================================================*/
void CGameRoomCommunity::update( const u32 timeMs )
{

	BuildingUpdate();
}

CGameRoomCommunity::~CGameRoomCommunity()
{
}