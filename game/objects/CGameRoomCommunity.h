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

class CGameRoomCommunity : public CGameRoom
{
public :

	CGameRoomCommunity(const OwnerType& owner,unsigned int objtype,  unsigned int btype, const ROOM_RESOURCE* res, 
		const vector3df& pos,
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));


	virtual		void						enter_control();

	virtual		void						update_control(CEventHandler* pReceiver) ;

	virtual		void						exit_control();

	virtual		void						update(const u32 timeMs);


	virtual		void						extra_node_setting() {	setOnebyOneNode(); };

	CGameRoomCommunity(const OwnerType& owner,unsigned int objtype,  unsigned int btype, const ROOM_RESOURCE* res);

	virtual		bool						HandleMessage(const Telegram& msg) {return true;}

	virtual ~CGameRoomCommunity();
};

#endif